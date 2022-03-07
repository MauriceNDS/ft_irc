#include "api/Group.hpp"
#include "api/exception/DuplicatedGroupException.hpp"

Group::Group(const string& identifier, Group *parent) : identifier(identifier), parent(parent) {
	if (parent)
		parent->addChild(this);
}

Group::~Group() {
	if (parent)
		parent->removeChild(getIdentifier());
	while (childs.size())
		delete childs.begin()->second;
}

const string& Group::getIdentifier() const {
	return identifier;
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

Group *Group::getParent() const {
	return parent;
}

Group *Group::getChild(const string& identifier) const {
	map<string, Group *>::const_iterator it = childs.find(identifier);
	if (it != childs.end())
		return it->second;
	return NULL;
}

// Events
void Group::onJoin(GroupJoinEvent::Before&) {}
void Group::onJoin(GroupJoinEvent::After&) {}
void Group::onLeave(GroupLeaveEvent&) {}

// Users
const set<User *>& Group::getUsers() const {
	return users;
}

bool Group::containsUser(const User& user) const {
	return users.find(const_cast<User *>(&user)) != users.end();
}

User *Group::findUser(const string& nickname) const {
	for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++) {
		User *user = *it;
		if (nickname == user->getName())
			return *it;
	}
	return NULL;
}

bool Group::canJoin(User& user) {
	if (containsUser(user))
		return true;

	if (parent && !parent->canJoin(user))
		return false;

	GroupJoinEvent::Before before(*this, user);
	onJoin(before);
	if (before.isCancelled())
		return false;

	return true;
}

void Group::addUserRecursive(User& user) {
	if (containsUser(user))
		return;

	if (parent)
		parent->addUserRecursive(user);

	users.insert(&user);

	GroupJoinEvent::After after(*this, user);
	onJoin(after);
}

bool Group::addUser(User *user) {
	return addUser(*user);
}

bool Group::addUser(User& user) {
	if (containsUser(user))
		return false;

	if (!canJoin(user))
		return false;

	if (parent)
		parent->addUser(user);

	addUserRecursive(user);
	return true;
}

void Group::removeUser(User& user) {
	demote(user);
	if (users.erase(&user)) {
		for (map<string, Group *>::iterator child = childs.begin(); child != childs.end(); child++)
			child->second->removeUser(user);

		GroupLeaveEvent event(*this, user);
		onLeave(event);
	}
}

set<User *>::size_type Group::size() const {
	return users.size();
}

bool Group::isEmpty() const {
	return users.empty();
}

// Operators (inherited)

set<User *> Group::getOperators() const {
	set<User *> all_operators = operators;
	if (parent) {
		set<User *> parent_operators = parent->getOperators();
		all_operators.insert(parent_operators.begin(), parent_operators.end());
	}
	return operators;
}

bool Group::isOperator(const User& user) const {
	if (!isLocalOperator(user)) {
		if (!parent || !parent->isOperator(user))
			return false;
	}
	return true;
}

// Operators (local)

const set<User *>& Group::getLocalOperators() const {
	return operators;
}

bool Group::isLocalOperator(const User& user) const {
	return operators.find(const_cast<User *>(&user)) != operators.end();
}

void Group::promote(User& user) {
	operators.insert(&user);
}

void Group::demote(User& user) {
	operators.erase(&user);
}
