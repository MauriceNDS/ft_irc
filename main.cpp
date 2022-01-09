#include "ft_irc.hpp"

#include "api/command/CommandManager.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

#include "api/User.hpp"
#include "core/command/elements/UserCommandElement.hpp"

#include "core/command/OperCommand.hpp"
#include "core/command/PartCommand.hpp"

int main(int argc, const char *argv[]) {
	CommandManager manager;

	manager.registerCommand(CommandSpec::Builder()
		.name("oper")
		.argument("list", GenericArguments::list<string>(GenericArguments::string()))
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.argument("optional", GenericArguments::optional(new UserCommandElement()))
		.executor(new OperCommand())
		.build()
	);
	manager.registerCommand(CommandSpec::Builder()
		.name("part")
		.argument("channels", GenericArguments::string())
		.argument("action", GenericArguments::string())
		.executor(new PartCommand())
		.build()
	);

	string input;
	int i = 0;
	while (++i < argc) {
		if (i > 1)
			input += " ";
		input += argv[i];
	}

	User *u = new User("Simon");
	manager.post(input, *u);
	delete u;
	return 0;
}
