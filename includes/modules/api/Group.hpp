#ifndef FT_IRC_API_GROUP
#define FT_IRC_API_GROUP

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Irc;

class Group {
private:
	const string& identifier;
	Group *const parent;
	map<string, Group *> childs;

	void addChild(Group *child);

protected:
	set<User *> users;
	set<User *> operators;

public:
	explicit Group(const string& identifier, Group *parent);

	const string& getIdentifier() const;
	Group *getParent() const;
	const map<string, Group *>& getChilds() const;

	// Users
	const set<User *>& getUsers() const;
	bool containsUser(User *user) const;	
	void addUser(User *user);
	void removeUser(User *user);

	virtual bool middleware(User *user);
	virtual void onJoin(User *user);

	// Operators
	const set<User *>& getOperators() const;
	bool isOperator(User *user) const;
	void promote(User *user);
	void demote(User *user);
};

#endif /* FT_IRC_API_GROUP */
