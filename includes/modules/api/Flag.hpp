#ifndef FT_IRC_API_FLAGS
#define FT_IRC_API_FLAGS

#include "ft_irc.hpp"

struct Flag {
	char sign;
	char letter;
	string value;

	Flag(char sign, char letter, string value = "") : sign(sign), letter(letter), value(value) {}
};

#endif /* FT_IRC_API_FLAGS */
