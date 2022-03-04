#ifndef FT_IRC_API_FLAGS
#define FT_IRC_API_FLAGS

#include "ft_irc.hpp"

struct Flag {
	char sign;
	char letter;
	string value;
	bool has_value;

	Flag(char sign, char letter, string value = "") : sign(sign), letter(letter), value(value), has_value(false) {}
};

#endif /* FT_IRC_API_FLAGS */
