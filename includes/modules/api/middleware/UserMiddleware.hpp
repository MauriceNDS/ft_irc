#ifndef FT_IRC_API_USER_MIDDLEWARE
#define FT_IRC_API_USER_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/middleware/Middleware.hpp"

#include "api/ResponseType.hpp"

class UserMiddleware : public Middleware {
public:
	bool handle(const Client& client) const {
		try {
			(void)dynamic_cast<const User&>(client);
			return true;
		} catch (const std::bad_cast& e) {}
		return false;
	};
};

#endif /* FT_IRC_API_USER_MIDDLEWARE */
