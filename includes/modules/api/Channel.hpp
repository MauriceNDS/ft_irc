#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Channel : public CommandSender {
private:
	string name;
    vector<User *> users;
	vector<User *> chanop;

public:
	Channel(const string& name) : name(name) {}

	const vector<User *>& getUsers() {
		return users;
	}
	
	void addUser(User *user) {
		if (!users.size())
			promoteChanop(user);
		users.push_back(user);
	}

	void removeUser(User *user) {
		for (vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
			if (*it == user) {
				users.erase(it);
				break ;
			}
		}
		if (!users.size())
			Irc::getInstance().removeChannel(this);
	}

	bool isChanop(User *user) {
		for (vector<User *>::iterator it = chanop.begin(); it != chanop.end(); it++) {
			if (*it == user)
				return (true);
		}
		return (false);
	}

	void promoteChanop(User *user)
	{
		for (vector<User *>::iterator it = chanop.begin(); it != chanop.end(); it++) {
			if (*it == user)
				return ;
		}
		chanop.push_back(user);
	}

	const string& getName() {
		return name;
	}

	void send(Response message) const {
		for (vector<User *>::const_iterator it = users.begin(); it != users.end(); it++)
			(*it)->send(message);
	}

	static bool isValidIdentifier(const string& identifier) {
		return identifier[0] == '#';
	}
};

#endif /* FT_IRC_API_CHANNEL */
