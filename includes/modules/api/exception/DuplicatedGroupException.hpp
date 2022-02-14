#ifndef FT_IRC_API_DUPLICATED_GROUP_EXCEPTION
#define FT_IRC_API_DUPLICATED_GROUP_EXCEPTION

#include <exception>

struct DuplicatedGroupException : public std::exception {

	const char *what() const throw () {
		return "The group already exists in the parent.";
	}
};

#endif /* FT_IRC_API_DUPLICATED_GROUP_EXCEPTION */
