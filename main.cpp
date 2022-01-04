#include "parsing/includes/CommandSpec.hpp"
#include "parsing/includes/CommandExecutor.hpp"
#include "parsing/includes/GenericArguments.hpp"

#include "core/includes/interface/User.hpp"
#include "core/includes/command/elements/UserCommandElement.hpp"

#include "core/includes/command/OperCommand.hpp"
#include "core/includes/command/PartCommand.hpp"

int main(int argc, const char *argv[]) {
	const CommandSpec oper = CommandSpec::Builder()
		.name("oper")
		.argument("list", GenericArguments::list<string>(GenericArguments::string()))
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.argument("optional", GenericArguments::optional(new UserCommandElement()))
		.executor(new OperCommand())
		.build();

	const CommandSpec part = CommandSpec::Builder()
		.name("oper")
		.argument("user", new UserCommandElement())
		.argument("action", GenericArguments::string())
		.executor(new PartCommand())
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
