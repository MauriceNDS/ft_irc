#include <iostream>

#include "core/includes/interface/User.hpp"
#include "core/includes/command/elements/UserCommandElement.hpp"

#include "parsing/includes/CommandSpec.hpp"
#include "parsing/includes/CommandExecutor.hpp"
#include "parsing/includes/GenericArguments.hpp"

class OperExecutor : public CommandExecutor {

	Response execute(Command cmd, CommandSender sender) {
		std::cout << "Oper called" << std::endl;
		return NONE;
	}
};

int main(int argc, char const *argv[])
{
	const CommandSpec oper = CommandSpec::Builder()
		.name("oper")
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.executor(new OperExecutor())
		.build();
	
	oper.call();
	return 0;
}
