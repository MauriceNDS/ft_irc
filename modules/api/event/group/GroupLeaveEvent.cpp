#include "api/event/group/GroupLeaveEvent.hpp"

GroupLeaveEvent::GroupLeaveEvent(Group& group, User& user) : group(group), user(user) {}

User& GroupLeaveEvent::getUser() {
	return user;
}

Group& GroupLeaveEvent::getGroup() {
	return group;
}
