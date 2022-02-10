#include "core/Irc.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"

bool Channel::isChanop(User *user) {
    set<User *>::iterator it = chanop.find(user);
    if (it == chanop.end()) {
        if (!Irc::getInstance().isOperator(user))
            return (false);
    }
    return (true);
}

void Channel::removeUser(User *user) {
    users.erase(user);
    chanop.erase(user);
    if (!users.size()) {
        Irc::getInstance().removeChannel(this);
    } else if (!chanop.size() && flags.reop) {
        chanop.insert(*users.begin());
    }
}
