#ifndef FT_IRC_API_GROUP
#define FT_IRC_API_GROUP

#include "ft_irc.hpp"

#include "api/User.hpp"

class Irc;
class GroupJoinEvent;

class Group {
private:
	const string& identifier;
	Group *const parent;
	map<string, Group *> childs;

	void addChild(Group *child);
	void removeChild(const string& identifier);

protected:
	set<User *> users;
	set<User *> operators;

public:
	explicit Group(const string& identifier, Group *parent);

	const string& getIdentifier() const;
	Group *getParent() const;
	const map<string, Group *>& getChilds() const;

	// Events
	virtual void onJoin(GroupJoinEvent& event);
	// virtual void onJoin(GroupJoinEvent::After& event);

	// Users
	const set<User *>& getUsers() const;
	bool containsUser(User *user) const;	
	bool addUser(User *user);
	void removeUser(User *user);

	// Operators
	const set<User *>& getOperators() const;
	bool isOperator(User *user) const;
	void promote(User *user);
	void demote(User *user);
};

#endif /* FT_IRC_API_GROUP */
