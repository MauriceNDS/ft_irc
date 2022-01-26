#include "ft_irc.hpp"

#include "core/Irc.hpp"

int main() {
	Irc irc("127.0.0.1:6697");
	ResponseSpec response1("300", "<nick> :Erroneous nickname");
	ResponseSpec response2("300", "OOOOOO");
	ResponseSpec response3("300", "C'est qui ? C'est <name> qui <adv> <last_name>.");

	std::cout << response1.build(irc.getServer(), "Saumon") << std::endl;
	std::cout << response2.build(irc.getServer()) << std::endl;
	std::cout << response3.build(irc.getServer(), "Manon", "te", "Berne") << std::endl;
	// irc.start();
	return 0;
}
