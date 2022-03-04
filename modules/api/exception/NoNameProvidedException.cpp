#include "api/exception/NoNameProvidedException.hpp"

const char *NoNameProvidedException::what() const throw () {
	return "Cannot initialize a command without a name.";
}