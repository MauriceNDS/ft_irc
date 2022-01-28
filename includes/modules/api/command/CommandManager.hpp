#ifndef FT_IRC_API_COMMAND_MANAGER
#define FT_IRC_API_COMMAND_MANAGER

#include "ft_irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandSpec.hpp"
#include "api/event/MessageEvent.hpp"

#include "api/exception/DuplicatedCommandException.hpp"

class CommandSpec;
class ResponseSpec;

class CommandManager {
private:
	map<string, const CommandSpec *> cspecs;
	map<string, const ResponseSpec *> rspecs;

public:
	void registerCommand(const CommandSpec *spec);
	void registerResponse(const ResponseSpec *spec);

	void process(MessageEvent& event);

	~CommandManager();
};

#endif /* FT_IRC_API_COMMAND_MANAGER */
