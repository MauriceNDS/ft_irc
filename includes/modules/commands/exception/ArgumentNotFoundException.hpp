#ifndef FT_IRC_CORE_ARGUMENT_NOT_FOUND_EXCEPTION
#define FT_IRC_CORE_ARGUMENT_NOT_FOUND_EXCEPTION

#include <exception>

struct ArgumentNotFoundException : public std::exception {

	const char *what() const throw () {
    	return "Unknown argument";
    }
};

#endif /* FT_IRC_CORE_ARGUMENT_NOT_FOUND_EXCEPTION */
