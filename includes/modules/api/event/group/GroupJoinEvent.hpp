#ifndef FT_IRC_API_GROUP_JOIN_EVENT
#define FT_IRC_API_GROUP_JOIN_EVENT

#include "api/Group.hpp"
#include "api/User.hpp"
#include "api/event/Cancellable.hpp"

class Group;

class GroupJoinEvent {
protected:
	Group& group;
	User& user;

public:
	GroupJoinEvent(Group& group, User& user);

	User& getUser();

	Group& getGroup();
};

class GroupJoinEventBefore : public GroupJoinEvent, public Cancellable {
public:
	GroupJoinEventBefore(Group& group, User& user);
};

class GroupJoinEventAfter : public GroupJoinEvent {
public:
	GroupJoinEventAfter(Group& group, User& user);
};

#endif /* FT_IRC_API_GROUP_JOIN_EVENT */
