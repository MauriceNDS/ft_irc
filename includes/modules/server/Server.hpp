#ifndef FT_IRC_API_SERVER
#define FT_IRC_API_SERVER

#include "ft_irc.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"

class Server {
private:
	string name;
    vector<Channel *> channels;
    vector<User *> users;
    
public:
	// TODO test
	Server(string name) : name(name) {}

	User *findUser(string & nickname) {
		for (iterator it = users.begin(); it != users.end(); it++)
			if ((*it).getNickName() == nickname)
				return *it;
		return NULL;
	}

	vector<Channel *> getChannels() {
		return channels;
	}
	vector<User *> getUsers() {
		return users;
	}
	const string& getName() {
		return name;
	}
};

#endif /* FT_IRC_API_SERVER */
