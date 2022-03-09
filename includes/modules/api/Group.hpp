#ifndef FT_IRC_API_GROUP
#define FT_IRC_API_GROUP

#include "ft_irc.hpp"

#include "api/event/group/GroupJoinEvent.hpp"
#include "api/event/group/GroupLeaveEvent.hpp"

class Irc;
class GroupJoinEvent;
class GroupJoinEventBefore;
class GroupJoinEventAfter;
class GroupLeaveEvent;

class Group {
private:
	bool alive;

	string identifier;
	Group *const parent;
	map<string, Group *> childs;

	void addChild(Group *child);
	void removeChild(const string& identifier);

	bool canJoin(User& user);
	void addUserRecursive(User& user);

	Group(const Group&);

protected:
	set<User *> users;
	set<User *> operators;

	// Listeners
	virtual void onJoin(GroupJoinEventBefore& event);
	virtual void onJoin(GroupJoinEventAfter& event);
	virtual void onLeave(GroupLeaveEvent& event);

public:
	explicit Group(const string& identifier, Group *parent = NULL);
	virtual ~Group();

	void kill();

	const string& getIdentifier() const;
	const map<string, Group *>& getChilds() const;
	Group *getParent() const;
	Group *getChild(const string& identifier) const;

	// Users
	const set<User *>& getUsers() const;
	User *findUser(const string& nickname) const;
	bool containsUser(const User& user) const;
	bool addUser(User *user);
	bool addUser(User& user);
	void removeUser(User& user);
	set<User *>::size_type size() const;
	bool isEmpty() const;

	// Operators (inherited)
	set<User *> getOperators() const;
	bool isOperator(const User& user) const;

	// Operators (local)
	const set<User *>& getLocalOperators() const;
	bool isLocalOperator(const User& user) const;
	void promote(User& user);
	void demote(User& user);
};

#endif /* FT_IRC_API_GROUP */
