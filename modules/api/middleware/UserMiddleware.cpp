#include "api/User.hpp"
#include "api/middleware/UserMiddleware.hpp"

bool UserMiddleware::handle(const Client& client) const {
	try {
		(void)dynamic_cast<const User&>(client);
		return true;
	} catch (...) {}
	return false;
}