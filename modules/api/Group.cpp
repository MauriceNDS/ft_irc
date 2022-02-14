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

void Group::removeChild(const string& name) {
	// TODO
	if (!childs.insert(make_pair(child->getIdentifier(), child)).second)
		throw DuplicatedGroupException();
}

// Users
const set<User *>& Group::getUsers() const {
	return users;
}

bool Group::containsUser(User *user) const {
	return users.find(user) != users.end();
}

void Group::addUser(User *user) {
	if (users.insert(user).second && parent)
		parent->addUser(user);
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
