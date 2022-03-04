#ifndef FT_IRC_API_ARGUMENT_NOT_FOUND_EXCEPTION
#define FT_IRC_API_ARGUMENT_NOT_FOUND_EXCEPTION

#include <exception>

struct ArgumentNotFoundException : public std::exception {

	const char *what() const throw ();
};

#endif /* FT_IRC_API_ARGUMENT_NOT_FOUND_EXCEPTION */
