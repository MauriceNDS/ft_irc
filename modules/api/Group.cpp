#include "api/Group.hpp"
#include "api/exception/DuplicatedGroupException.hpp"

Group::Group(const string& identifier, Group *parent) : identifier(identifier), parent(parent) {
	if (parent)
		parent->addChild(this);
}

const string& Group::getIdentifier() const {
	return identifier;
}

Group *Group::getParent() const {
	return parent;
}

const map<string, Group *>& Group::getChilds() const {
	return childs;
}

void Group::addChild(Group *child) {
	if (!childs.insert(make_pair(child->getIdentifier(), child)).second)
		throw DuplicatedGroupException();
}

void Group::removeChild(const string& identifier) {
	childs.erase(identifier);
}

#include "api/event/GroupJoinEvent.hpp"

// Events
void Group::onJoin(GroupJoinEvent&) {}
// void Group::onJoin(GroupJoinEvent::Before& event) {}
// void Group::onJoin(GroupJoinEvent::After& event) {}

// Users
const set<User *>& Group::getUsers() const {
	return users;
}

bool Group::containsUser(User *user) const {
	return users.find(user) != users.end();
}

bool Group::addUser(User *user) {
	if (containsUser(user))
		return true;

	GroupJoinEvent::Before before(*this, *user);
	onJoin(before);

	if (before.isCancelled())
		return false;
	if (parent && !parent->addUser(user))
		return false;
	users.insert(user);

	GroupJoinEvent::After after(*this, *user);
	onJoin(after);
	return true;
}

void Group::removeUser(User *user) {
	set<User *>::iterator it = users.find(user);
	if (it != users.end()) {
		users.erase(it);
		for (map<string, Group *>::iterator child = childs.begin(); child != childs.end(); child++)
			child->second->removeUser(user);
	}
}

// Operators

const set<User *>& Group::getOperators() const {
	return operators;
}

bool Group::isOperator(User *user) const {
	set<User *>::iterator it = operators.find(user);
	if (it == operators.end()) {
		if (!parent || !parent->isOperator(user))
			return false;
	}
	return true;
}

void Group::promote(User *user) {
	operators.insert(user);
}

void Group::demote(User *user) {
	set<User *>::iterator it = operators.find(user);
	if (it != operators.end())
		operators.insert(user);
}
