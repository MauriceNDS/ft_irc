#ifndef FT_IRC_API_REGISTERED_USER_MIDDLEWARE
#define FT_IRC_API_REGISTERED_USER_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/middleware/Middleware.hpp"

class RegisteredUserMiddleware : public Middleware {
public:
	bool handle(const Client& client) const;
};

#endif /* FT_IRC_API_REGISTERED_USER_MIDDLEWARE */
