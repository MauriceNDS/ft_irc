#ifndef FT_IRC_API_NAMEABLE
#define FT_IRC_API_NAMEABLE

#include "ft_irc.hpp"

class Nameable {
public:
	virtual const std::string& getName() const = 0;

	virtual ~Nameable() {}
};

#endif /* FT_IRC_API_NAMEABLE */
