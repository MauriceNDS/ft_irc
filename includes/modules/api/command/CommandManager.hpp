#ifndef FT_IRC_API_COMMAND_MANAGER
#define FT_IRC_API_COMMAND_MANAGER

#include "ft_irc.hpp"

#include "api/ResponseType.hpp"

#include "api/User.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/event/MessageEvent.hpp"

#include "api/exception/CommandNotFoundException.hpp"
#include "api/exception/DuplicatedCommandException.hpp"

class CommandSpec;

class CommandManager {
private:
	map<string, const CommandSpec *> specs;

public:
	void registerCommand(const CommandSpec *spec);

	void post(MessageEvent& event);

	~CommandManager();
};

#endif /* FT_IRC_API_COMMAND_MANAGER */
