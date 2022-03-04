#include "api/User.hpp"
#include "api/ResponseTypes.hpp"

#include "core/middleware/RegisteredUserMiddleware.hpp"

bool RegisteredUserMiddleware::handle(const Client& client) const {
	try {
		const User& user = dynamic_cast<const User&>(client);
		if (user.isRegistered())
			return true;
		else
			user.send(ResponseTypes::ERR_NOTREGISTERED());
	} catch (...) {}
	return false;
}
