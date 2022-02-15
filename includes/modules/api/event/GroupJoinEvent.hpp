#ifndef FT_IRC_API_GROUP_JOIN_EVENT
#define FT_IRC_API_GROUP_JOIN_EVENT

#include "api/Group.hpp"
#include "api/User.hpp"
#include "api/event/Cancellable.hpp"

class GroupJoinEvent {
protected:
	Group& group;
	User& user;

public:
	GroupJoinEvent(Group& group, User& user) : group(group), user(user) {}

	User& getUser() {
		return user;
	}

	Group& getGroup() {
		return group;
	}

	class Before;
	class After;
};

class GroupJoinEvent::Before : public GroupJoinEvent, public Cancellable {
public:
	Before(Group& group, User& user) : GroupJoinEvent(group, user) {}
};

class GroupJoinEvent::After : public GroupJoinEvent {
public:
	After(Group& group, User& user) : GroupJoinEvent(group, user) {}
};

#endif /* FT_IRC_API_GROUP_JOIN_EVENT */
