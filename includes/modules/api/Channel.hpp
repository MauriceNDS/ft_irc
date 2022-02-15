#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"
// #include "core/Irc.hpp"

#include "api/CommandSender.hpp"
#include "api/User.hpp"

class Irc;

struct Modes {
	bool anonymous;
	bool invite;
	bool moderate;
	bool outside_message;
	bool priv;
	bool secret;
	bool reop;
	bool topic;
	string password;
	size_t user_limit;

	Modes() : anonymous(false), invite(false), moderate(false), outside_message(false), priv(false), secret(false), reop(false), topic(true), user_limit(0) {}
};

class Channel : public CommandSender {
private:
	string name;
	string topic;
	set<User *> users;
	set<User *> chanop;
	set<User *> voiceop;
	set<User *> invite;
	Modes flags;

public:
	Channel(const string& name) : name(name) {}

	const set<User *>& getUsers() {
		return users;
	}

	const set<User *>& getInvite() {
		return invite;
	}

	Modes& getFlag() {
		return flags;
	}
	string& getPassword() {
		return flags.password;
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

	bool isVoiceOp(User *user) {
		set<User *>::iterator it = voiceop.find(user);
		if (it == users.end() && !isChanop(user))
			return false;
		return true;
	};

	bool isChanop(User *user);

	bool isOnChan(User *user) {
		set<User *>::iterator it = users.find(user);
		if (it == users.end())
			return false;
		return true;
	}

	void promoteVoiceOp(User *user)
	{
		if (!user)
			return;
		set<User *>::iterator it = voiceop.find(user);
		if (it == voiceop.end())
			voiceop.insert(user);
	}

	void demoteVoiceOp(User *user) {
		if (!user)
			return;
		set<User *>::iterator it = voiceop.find(user);
		if (it == voiceop.end())
			voiceop.erase(user);
	}

	void promoteChanop(User *user) {
		if (!user)
			return;
		set<User *>::iterator it = chanop.find(user);
		if (it == chanop.end())
			chanop.insert(user);
	}

	void demoteChanop(User *user) {
		if (!user)
			return;
		set<User *>::iterator it = chanop.find(user);
		if (it == chanop.end())
			chanop.erase(user);
		if (!chanop.size() && flags.reop)
        	chanop.insert(*users.begin());
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
