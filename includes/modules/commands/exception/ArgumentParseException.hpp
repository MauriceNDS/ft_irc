#ifndef FT_IRC_CORE_ARGUMENT_PARSE_EXCEPTION
#define FT_IRC_CORE_ARGUMENT_PARSE_EXCEPTION

#include <exception>

#include "ft_irc.hpp"

struct ArgumentParseException : public std::logic_error {
	ArgumentParseException(const string& message) : std::logic_error(message) {}
};

#endif /* FT_IRC_CORE_ARGUMENT_PARSE_EXCEPTION */
