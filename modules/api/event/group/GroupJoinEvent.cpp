#include "api/event/group/GroupJoinEvent.hpp"

GroupJoinEvent::GroupJoinEvent(Group& group, User& user) : group(group), user(user) {}

User& GroupJoinEvent::getUser() {
	return user;
}

Group& GroupJoinEvent::getGroup() {
	return group;
}

GroupJoinEventBefore::GroupJoinEventBefore(Group& group, User& user) : GroupJoinEvent(group, user) {}

GroupJoinEventAfter::GroupJoinEventAfter(Group& group, User& user) : GroupJoinEvent(group, user) {}
