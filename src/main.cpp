#include <iostream>

#include "command/CommandSpec.hpp"
#include "command/CommandExecutor.hpp"
#include "command/GenericArguments.hpp"
#include "User.hpp"

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
