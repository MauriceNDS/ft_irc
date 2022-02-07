#ifndef FT_IRC_CORE_PASS_COMMAND
#define FT_IRC_CORE_PASS_COMMAND

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/User.hpp"
#include "api/command/CommandExecutor.hpp"

#include "api/ResponseTypes.hpp"

class PassCommand : public CommandExecutor {

	void execute(const Command& cmd, CommandSender& sender) {
        User& user = static_cast<User &>(sender);

		string& password = cmd.getArg<string>("password");
        if (user.isRegistered()) {
            user.send(ResponseTypes::ERR_ALREADYREGISTRED());
        } else if (Irc::getInstance().getServer().getPassword() != password) {
            Client& client = static_cast<Client &>(sender);
            client.getConnection()->closeConnection = true;
        } else {
            user.setValidPassword(true);
        }
	}
};

#endif /* FT_IRC_CORE_PASS_COMMAND */
