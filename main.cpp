#include <iostream>

#include "core/includes/interface/User.hpp"
#include "core/includes/command/elements/UserCommandElement.hpp"

#include "parsing/includes/CommandSpec.hpp"
#include "parsing/includes/CommandExecutor.hpp"
#include "parsing/includes/GenericArguments.hpp"

class OperExecutor : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
		(void)sender;
		std::cout << "Oper called" << std::endl;

		User& user = cmd.getArg<User>("user");
		string& action = cmd.getArg<string>("action");

		std::cout << user.getName() << std::endl;
		std::cout << "---" << std::endl;
		std::cout << action << std::endl;

		return NONE;
	}
};

int main(int argc, char const *argv[]) {
	(void)argc;
	(void)argv;

	const CommandSpec oper = CommandSpec::Builder()
		.name("oper")
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.executor(new OperExecutor())
		.build();

	oper.call();
	return 0;
}
