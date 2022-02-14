#ifndef FT_IRC_API_CHANNEL_JOIN_EVENT
#define FT_IRC_API_CHANNEL_JOIN_EVENT

#include "api/Group.hpp"
#include "api/User.hpp"
#include "api/event/Cancellable.hpp"

class GroupJoinEvent {
protected:
	Group& group;
	User& user;

public:
	ChannelJoinEvent(Group& group, User& user) : group(group), user(user) {}

	User& getUser() {
		return user;
	}

	Group& getGroup() {
		return group;
	}

	class Before;
	class After;
};

class ChannelJoinEvent::Before : public ChannelJoinEvent, public Cancellable {
	ChannelJoinEvent::Before(Group& group, User& user) : ChannelJoinEvent(group, user);
};

class ChannelJoinEvent::After {
	ChannelJoinEvent::After(Group& group, User& user) : ChannelJoinEvent(group, user);
};

#endif /* FT_IRC_API_CHANNEL_JOIN_EVENT */
