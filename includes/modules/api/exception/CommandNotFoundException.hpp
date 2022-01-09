#ifndef FT_IRC_API_COMMAND_NOT_FOUND_EXCEPTION
#define FT_IRC_API_COMMAND_NOT_FOUND_EXCEPTION

#include <exception>

struct CommandNotFoundException : public std::exception {

	const char *what() const throw () {
    	return "Command not found";
    }
};

#endif /* FT_IRC_API_COMMAND_NOT_FOUND_EXCEPTION */
