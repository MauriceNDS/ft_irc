#include "core/Irc.hpp"
#include "core/command/OperCommand.hpp"
#include "core/command/PartCommand.hpp"
#include "core/command/elements/UserCommandElement.hpp"

#include "api/command/CommandSpec.hpp"
#include "api/command/GenericArguments.hpp"

void Irc::start() {
	commandManager.registerCommand(CommandSpec::Builder()
		.name("OPER")
		.argument("list", GenericArguments::list<User>(new UserCommandElement()))
		.argument("action", GenericArguments::string())
		.argument("optional", GenericArguments::optional(new UserCommandElement()))
		.executor(new OperCommand())
		.build()
	);

	commandManager.registerCommand(CommandSpec::Builder()
		.name("PART")
		.argument("channels", GenericArguments::string())
		.argument("action", GenericArguments::string())
		.executor(new PartCommand())
		.build()
	);
	server.listen();
}

Irc *Irc::instance = nullptr;
