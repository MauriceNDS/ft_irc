#ifndef FT_IRC_API_VALID_PASS_MIDDLEWARE
#define FT_IRC_API_VALID_PASS_MIDDLEWARE

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/middleware/Middleware.hpp"

#include "api/ResponseTypes.hpp"

class ValidPassMiddleware : public Middleware {
public:
	bool handle(const Client& client) const {
		try {
			const User& user = dynamic_cast<const User&>(client);
			if (user.getValidPassword())
				return true;
			else
				user.send(ResponseTypes::ERR_NOVALIDPASS());
		} catch (const std::bad_cast& e) {}
		return false;
	};
};

#endif /* FT_IRC_API_VALID_PASS_MIDDLEWARE */
