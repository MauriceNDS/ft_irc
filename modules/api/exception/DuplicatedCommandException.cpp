#include "api/exception//DuplicatedCommandException.hpp"

const char *DuplicatedCommandException::what() const throw () {
	return "This command already exists.";
}