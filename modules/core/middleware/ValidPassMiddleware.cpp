#include "api/User.hpp"
#include "api/ResponseTypes.hpp"
#include "core/middleware/ValidPassMiddleware.hpp"

bool ValidPassMiddleware::handle(const Client& client) const {
	try {
		const User& user = dynamic_cast<const User&>(client);
		if (user.getValidPassword())
			return true;
		else
			user.send(ResponseTypes::ERR_NOVALIDPASS());
	} catch (...) {}
	return false;
};
