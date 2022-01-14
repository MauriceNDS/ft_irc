#ifndef FT_IRC_API_MIDDLEWARE
#define FT_IRC_API_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/Client.hpp"

class Middleware {
public:
	virtual bool handle(const Client& client) const = 0;

	virtual ~Middleware() {}
};

#endif /* FT_IRC_API_MIDDLEWARE */

