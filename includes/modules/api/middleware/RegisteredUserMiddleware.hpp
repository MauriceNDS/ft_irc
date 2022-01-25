#ifndef FT_IRC_API_REGISTERED_USER_MIDDLEWARE
#define FT_IRC_API_REGISTERED_USER_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/middleware/Middleware.hpp"

#include "api/ResponseType.hpp"

class RegisteredUserMiddleware : public Middleware {
public:
	bool handle(const Client& client) const {
		try {
			const User& user = dynamic_cast<const User&>(client);
			if (user.isRegistered())
				return true;
			else
				user.send(ERR_NOTREGISTERED);
		} catch (const std::bad_cast& e) {}
		return false;
	};
};

#endif /* FT_IRC_API_REGISTERED_USER_MIDDLEWARE */
