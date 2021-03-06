#ifndef FT_IRC_API_VALID_PASS_MIDDLEWARE
#define FT_IRC_API_VALID_PASS_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/middleware/Middleware.hpp"

class ValidPassMiddleware : public Middleware {
public:
	bool handle(const Client& client) const;
};

#endif /* FT_IRC_API_VALID_PASS_MIDDLEWARE */
