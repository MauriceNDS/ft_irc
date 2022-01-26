#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"
// #include "core/Irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Irc;

class Channel : public CommandSender {
private:
	string name;
    set<User *> users;
	set<User *> chanop;

public:
	Channel(const string& name) : name(name) {}

	const set<User *>& getUsers() {
		return users;
	}
	
	void addUser(User *user) {
		if (!users.size())
			promoteChanop(user);
		users.insert(user);
	}

	void removeUser(User *user);

	bool isChanop(User *user);

	void promoteChanop(User *user)
	{
		set<User *>::iterator it = chanop.find(user);
		if (it == chanop.end())
			chanop.insert(user);
	}

	const string& getName() {
		return name;
	}

	void send(Response message) const {
		for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++)
			(*it)->send(message);
	}

	static bool isValidIdentifier(const string& identifier) {
		return identifier[0] == '#';
	}
};

#endif /* FT_IRC_API_CHANNEL */
