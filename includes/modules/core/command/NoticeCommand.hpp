#ifndef FT_IRC_CORE_NOTICE_COMMAND
#define FT_IRC_CORE_NOTICE_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"
#include "core/command/element/MsgToCommandElement.hpp"

#include "api/ResponseTypes.hpp"

class NoticeCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender);
};

#endif /* FT_IRC_CORE_NOTICE_COMMAND */
