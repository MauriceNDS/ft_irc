#include "ft_irc.hpp"

#include <sstream>

string itos(int value) {
	std::ostringstream out;
	out << value;
	return out.str();
}
