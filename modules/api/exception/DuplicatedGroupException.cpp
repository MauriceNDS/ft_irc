#include "api/exception/DuplicatedGroupException.hpp"

const char *DuplicatedGroupException::what() const throw () {
	return "The group already exists in the parent.";
}