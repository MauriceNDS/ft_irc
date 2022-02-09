#ifndef FT_IRC_API_DUPLICATED_COMMAND_EXCEPTION
#define FT_IRC_API_DUPLICATED_COMMAND_EXCEPTION

#include <exception>

struct DuplicatedCommandException : public std::exception {

	const char *what() const throw () {
		return "This command already exists.";
	}
};

#endif /* FT_IRC_API_DUPLICATED_COMMAND_EXCEPTION */
