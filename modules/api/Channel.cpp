#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"

Modes::Modes() : invite(false), moderate(false), outside_message(false), priv(false), secret(false), reop(false), topic(true), user_limit(0) {}

Channel::Channel(const string& name) : Group(name, &Irc::getInstance()) {
	std::cout << "[INFO] " << getName() << " created" << std::endl;
}

Channel::~Channel() {
	std::cout << "[INFO] " << getName() << " destroyed" << std::endl;
}

void Channel::onJoin(GroupJoinEventBefore& event) {
	User& user = event.getUser();

	if (getFlags().invite && !isInvited(user)) {
		user.send(ResponseTypes::ERR_INVITEONLYCHAN(getName().c_str()));
		event.setCancelled(true);
	} else if (getFlags().user_limit && size() >= getFlags().user_limit) {
		user.send(ResponseTypes::ERR_CHANNELISFULL(getName().c_str()));
		event.setCancelled(true);
	}
}

void Channel::onJoin(GroupJoinEventAfter& event) {
	User& user = event.getUser();

	if (size() == 1)
		promote(event.getUser());

	send(ResponseTypes::JOIN(user, getName().c_str()));

	for (set<User *>::const_iterator entry = getUsers().begin(); entry != getUsers().end(); entry++)
		user.send(ResponseTypes::RPL_NAMREPLY(user.getName().c_str(), getSymbol().c_str(), getName().c_str(), getDisplayName(*(*entry)).c_str()));

	user.send(ResponseTypes::RPL_ENDOFNAMES(user.getName().c_str(), getName().c_str()));

	std::cout << "[INFO] " << event.getUser().getName() << " joined " << getName() << std::endl;
}

void Channel::onLeave(GroupLeaveEvent& event) {
	std::cout << "[INFO] " << event.getUser().getName() << " left " << getName() << std::endl;
	if (isEmpty()) {
		event.getGroup().kill();
	} else {
		if (flags.reop && getLocalOperators().size() == 0) {
			promote(*(*(getUsers().begin())));
		}
	}
}

const set<User *>& Channel::getInvites() const {
	return invite;
}

Modes& Channel::getFlags() {
	return flags;
}

const Modes& Channel::getFlags() const {
	return flags;
}

string Channel::getSymbol() const {
	if (getFlags().secret)
		return "@";
	if (getFlags().priv)
		return "*";
	return "=";
}

const string& Channel::getPassword() const {
	return flags.password;
}

void Channel::setPassword(const string& password) {
	flags.password = password;
}

bool Channel::isInvited(User& user) const {
	return invite.find(&user) != invite.end();
}

void Channel::addInvite(User& user) {
	invite.insert(&user);
}

bool Channel::isVoiceOp(const User& user) const {
	return voiceop.find(const_cast<User *>(&user)) != voiceop.end();
}

string Channel::getDisplayName(const User& user) const{
	if (isLocalOperator(user))
		return ("@" + user.getName());
	else if (isVoiceOp(user))
		return ("+" + user.getName());
	return user.getName();
}

void Channel::promoteVoiceOp(User& user) {
	voiceop.insert(&user);
}

void Channel::demoteVoiceOp(User& user) {
	voiceop.erase(&user);
}

const string Channel::getTopic() const {
	if (topic.empty())
		return "No topic is set";
	return topic;
}

void Channel::setTopic(string& arg) {
	topic = arg;
}

string Channel::getName() const {
	return getIdentifier();
}

string Channel::getSenderName() const {
	return getName() + "!" + Irc::getInstance().getServer().getConnection().getIP();
}

void Channel::send(const string& message) const {
	for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++)
		(*it)->send(message);
}

void Channel::send(const CommandSender& sender, const string& message) const {
	for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++) {
		User *user = *it;
		if (user != &sender) {
			user->send(message);
		}
	}
}

bool Channel::isValidIdentifier(const string& identifier) {
	return identifier[0] == '#';
}
