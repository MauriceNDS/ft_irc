#include "ft_irc.hpp"

#include "core/Irc.hpp"

int main() {
	Server server("ft_irc");
	server.start();
	return 0;
}
