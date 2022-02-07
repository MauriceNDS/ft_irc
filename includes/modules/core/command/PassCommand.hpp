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
            if (user.isRegistered()) {
			user.send(ResponseTypes::RPL_WELCOME(user.getNickName().c_str(), user.getUserName().c_str(), Irc::getInstance().getServer().getHost().c_str()));
			user.send(ResponseTypes::RPL_YOURHOST(Irc::getInstance().getServer().getName().c_str(), VERSION));
			user.send(ResponseTypes::RPL_CREATED(CREATION_DATE));
			user.send(ResponseTypes::RPL_MYINFO(Irc::getInstance().getServer().getName().c_str(), VERSION, "0", "0"));
		    }
        }
	}
};

#endif /* FT_IRC_CORE_PASS_COMMAND */
