#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/Channel.hpp"

Channel::Channel(const string& name) : name(name) {}

const set<User *>& Channel::getUsers() {
    return users;
}

const set<User *>& Channel::getInvite() {
    return invite;
}

Modes& Channel::getFlag() {
    return flags;
}

string& Channel::getPassword() {
    return flags.password;
}

void Channel::addUser(User *user) {
    if (!users.size())
        promoteChanop(user);
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
    for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++)
        (*it)->send(message);
}

string Channel::getSenderName() const {
	return Irc::getInstance().getServer().getSenderName();
}

bool Channel::isValidIdentifier(const string& identifier) {
    return identifier[0] == '#';
}
