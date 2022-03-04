#ifndef FT_IRC_API_OPERATOR_MIDDLEWARE
#define FT_IRC_API_OPERATOR_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/middleware/Middleware.hpp"

class OperatorMiddleware : public Middleware {
public:
	bool handle(const Client& client) const;
};

#endif /* FT_IRC_API_OPERATOR_MIDDLEWARE */
