#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"
// #include "core/Irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Irc;

struct flag {
	bool anonymous;
	bool invite;
	bool moderate;
	bool outside_message;
	bool quiet;
	bool priv;
	bool secret;
	bool reop;
	bool topic;
	bool password;
	size_t user_limit;
};

class Channel : public CommandSender {
private:
	string name;
	string topic;
	string password;
	set<User *> users;
	set<User *> chanop;
	set<User *> voice_priv;
	set<User *> invite;
	flag flags;

public:
	Channel(const string& name) : name(name) {
	flags.anonymous = false; flags.invite = false; flags.moderate = false;
	flags.outside_message = false; flags.quiet = false; flags.priv = false;
	flags.secret = false; flags.reop = false; flags.topic = false;
	flags.password = false; flags.user_limit = 0;}

	const set<User *>& getUsers() {
		return users;
	}

	const set<User *>& getInvite() {
		return invite;
	}

	const flag& getFlag() {
		return flags;
	}
	const string& getPassword() {
		return password;
	}
	
	void addUser(User *user) {
		if (!users.size())
			promoteChanop(user);
		users.insert(user);
	}

	void addInvite(User *user) {
		if (invite.find(user) != invite.end())
			invite.insert(user);
	}

	void removeUser(User *user);

	bool isChanop(User *user);

	bool isOnChan(User *user)
	{
		set<User *>::iterator it = users.find(user);
		if (it == users.end())
			return false;
		return true;
	}

	void promoteChanop(User *user)
	{
		set<User *>::iterator it = chanop.find(user);
		if (it == chanop.end())
			chanop.insert(user);
	}

	const string getTopic() const {
		if (topic.empty())
			return "No topic is set";
		return topic;
	}

	void setTopic(string& arg) {
		topic = arg;
	}
	
	const string& getName() const {
		return name;
	}

	void send(const string& message) const {
		for (set<User *>::const_iterator it = users.begin(); it != users.end(); it++)
			(*it)->send(message);
	}

	static bool isValidIdentifier(const string& identifier) {
		return identifier[0] == '#';
	}
};

#endif /* FT_IRC_API_CHANNEL */
