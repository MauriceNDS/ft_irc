#include <iostream>

#include "core/includes/interface/User.hpp"
#include "core/includes/command/elements/UserCommandElement.hpp"

#include "parsing/includes/CommandSpec.hpp"
#include "parsing/includes/CommandExecutor.hpp"
#include "parsing/includes/GenericArguments.hpp"

class OperCommand : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
		(void)sender;
		std::cout << "==== OPER ====" << std::endl;

		User& user = cmd.getArg<User>("user");
		string& action = cmd.getArg<string>("action");
		User*& optional = cmd.getArg<User*>("optional");

		std::cout << user.getName() << std::endl;
		std::cout << "---" << std::endl;
		std::cout << action << std::endl;
		std::cout << "---" << std::endl;
		if (optional)
			std::cout << "Optional user found" << std::endl;
		else
			std::cout << "Optional user not found" << std::endl;

		return NONE;
	}
};

class PartCommand : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
		(void)sender;
		std::cout << "==== PART ====" << std::endl;

		string& user = cmd.getArg<string>("channels");
		string& action = cmd.getArg<string>("action");

		std::cout << user << std::endl;
		std::cout << "---" << std::endl;
		std::cout << action << std::endl;

		return NONE;
	}
};

int main(int argc, const char *argv[]) {
	const CommandSpec oper = CommandSpec::Builder()
		.name("oper")
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.argument("optional", GenericArguments::optional(new UserCommandElement()))
		.executor(new OperCommand())
		.build();

	const CommandSpec part = CommandSpec::Builder()
		.name("oper")
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.executor(new OperCommand())
		.build();

	string input;
	int i;

	i = 0;
	while (++i < argc) {
		if (i > 1)
			input += " ";
		input += argv[i];
	}

	oper.call(input);
	return 0;
}
