#include "ft_irc.hpp"

#include "core/Irc.hpp"

int main() {
	Irc irc("127.0.0.1:6697");
	irc.start();
	return 0;
}
