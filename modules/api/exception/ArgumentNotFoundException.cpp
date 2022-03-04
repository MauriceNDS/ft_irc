#include "api/exception/ArgumentNotFoundException.hpp"

const char *ArgumentNotFoundException::what() const throw () {
	return "Unknown argument";
}