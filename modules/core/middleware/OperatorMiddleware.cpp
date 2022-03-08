#include "core/Irc.hpp"
#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

#include "core/middleware/OperatorMiddleware.hpp"

bool OperatorMiddleware::handle(const Client& client) const {
	try {
		const User& user = dynamic_cast<const User&>(client);
		if (user.isRegistered()) {
			if (Irc::getInstance().isOperator(user))
				return true;
			else
				user.send(ResponseTypes::ERR_NOPRIVILEGES(user.getName().c_str()));
		}
		else
			user.send(ResponseTypes::ERR_NOTREGISTERED());
	} catch (...) {}
	return false;
}
