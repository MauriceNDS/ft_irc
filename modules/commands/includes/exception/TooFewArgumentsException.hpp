#ifndef FT_IRC_CORE_TOO_FEW_ARGUMENTS_EXCEPTION
#define FT_IRC_CORE_TOO_FEW_ARGUMENTS_EXCEPTION

#include <exception>

struct TooFewArgumentsException : public std::exception {

	const char *what() const throw () {
    	return "Too few arguments";
    }
};

#endif /* FT_IRC_CORE_TOO_FEW_ARGUMENTS_EXCEPTION */
