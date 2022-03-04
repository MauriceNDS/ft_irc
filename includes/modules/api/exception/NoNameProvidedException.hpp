#ifndef FT_IRC_API_NO_NAME_PROVIDED_EXCEPTION
#define FT_IRC_API_NO_NAME_PROVIDED_EXCEPTION

#include <exception>

struct NoNameProvidedException : public std::exception {

	const char *what() const throw ();
};

#endif /* FT_IRC_API_NO_NAME_PROVIDED_EXCEPTION */
