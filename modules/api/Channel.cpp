#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"

Channel::Channel(const string& name) : name(name) {}

const set<User *>& Channel::getUsers() const {
	return users;
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

void Channel::addUser(User *user) {
	if (!users.size())
		promoteChanop(user);
	if (invite.find(user) != invite.end())
		invite.erase(user);
	users.insert(user);
}

void Channel::removeUser(User *user) {
	users.erase(user);
	chanop.erase(user);
	if (!users.size()) {
		Irc::getInstance().removeChannel(this);
	} else if (!chanop.size() && flags.reop) {
		chanop.insert(*users.begin());
	}
}

void Channel::addInvite(User *user) {
	if (invite.find(user) != invite.end())
		invite.insert(user);
}

bool Channel::isVoiceOp(User *user) {
	set<User *>::iterator it = voiceop.find(user);
	if (it == users.end() && !isChanop(user))
		return false;
	return true;
};

bool Channel::isChanop(User *user) {
	set<User *>::iterator it = chanop.find(user);
	if (it == chanop.end()) {
		if (!Irc::getInstance().isOperator(user))
			return (false);
	}
	return (true);
}

bool Channel::isOnChan(User *user) {
	set<User *>::iterator it = users.find(user);
	if (it == users.end())
		return false;
	return true;
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
	if (it == voiceop.end())
		voiceop.erase(user);
}

void Channel::promoteChanop(User *user) {
	if (!user)
		return;
	set<User *>::iterator it = chanop.find(user);
	if (it == chanop.end())
		chanop.insert(user);
}

void Channel::demoteChanop(User *user) {
	if (!user)
		return;
	set<User *>::iterator it = chanop.find(user);
	if (it == chanop.end())
		chanop.erase(user);
	if (!chanop.size() && flags.reop)
		chanop.insert(*users.begin());
}

const string Channel::getTopic() const {
	if (topic.empty())
		return "No topic is set";
	return topic;
}

void Channel::setTopic(string& arg) {
	topic = arg;
}

const string& Channel::getName() const {
	return name;
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

string Channel::getSenderName() const {
	return getName() + "!" + Irc::getInstance().getServer().getConnection().getIP();
}

bool Channel::isValidIdentifier(const string& identifier) {
	return identifier[0] == '#';
}
