#ifndef FT_IRC_API_GROUP_LEAVE_EVENT
#define FT_IRC_API_GROUP_LEAVE_EVENT

#include "api/Group.hpp"
#include "api/User.hpp"
#include "api/event/Cancellable.hpp"

class Group;

class GroupLeaveEvent {
protected:
	Group& group;
	User& user;

public:
	GroupLeaveEvent(Group& group, User& user);

	User& getUser();

	Group& getGroup();
};

#endif /* FT_IRC_API_GROUP_LEAVE_EVENT */
