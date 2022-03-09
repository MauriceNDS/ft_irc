#ifndef FT_IRC_API_DUPLICATED_GROUP_EXCEPTION
#define FT_IRC_API_DUPLICATED_GROUP_EXCEPTION

#include <exception>

struct DuplicatedGroupException : public std::exception {

	const char *what() const throw ();
};

#endif /* FT_IRC_API_DUPLICATED_GROUP_EXCEPTION */
