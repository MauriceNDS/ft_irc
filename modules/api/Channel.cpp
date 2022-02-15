#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"

Channel::Channel(const string& name) : Group(name, NULL) {}

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

void Channel::addInvite(User *user) {
	if (invite.find(user) == invite.end())
		invite.insert(user);
}

bool Channel::isVoiceOp(User *user) {
	set<User *>::iterator it = voiceop.find(user);
	if (it == voiceop.end() && !isOperator(user))
		return false;
	return true;
};

string Channel::getTaggedUserName(User *user) const{
	if (user && users.find(user) != users.end()) {
		if (this->chanop.find(user) != chanop.end())
			return ("@" + user->getName());
		else if (this->voiceop.find(user) != voiceop.end())
			return ("+" + user->getName());
	}
	return user->getName();
}

void Channel::promoteVoiceOp(User *user) {
	if (!user)
		return;
	set<User *>::iterator it = voiceop.find(user);
	if (it == voiceop.end())
		voiceop.insert(user);
}

void Channel::demoteVoiceOp(User *user) {
	if (!user)
		return;
	set<User *>::iterator it = voiceop.find(user);
	if (it != voiceop.end())
		voiceop.erase(user);
}

const string Channel::getTopic() const {
	if (topic.empty())
		return "No topic is set";
	return topic;
}

void Channel::setTopic(string& arg) {
	topic = arg;
}

string Channel::getSenderName() const {
	return getName() + "!" + Irc::getInstance().getServer().getConnection().getIP();
}

void Channel::send(const string& message) const {
	std::cout << "          }-- " << message.c_str();
	for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++)
		(*it)->send(message);
}

void Channel::send(const CommandSender& sender, const string& message) const {
	std::cout << "          }-- " << message.c_str();
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
