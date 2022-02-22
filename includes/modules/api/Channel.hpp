#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"

#include "api/CommandSender.hpp"

class Irc;
class User;

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
	Channel(const string& name);

	const string& getName() const;
	string getSenderName() const;

	void send(const string& message) const;

	const set<User *>& getUsers();
	const set<User *>& getInvite();

	Modes& getFlag();
	string& getPassword();

	void addUser(User *user);
	void removeUser(User *user);

	void addInvite(User *user);

	bool isChanop(User *user);
	bool isVoiceOp(User *user);

	bool isOnChan(User *user);

	void promoteChanop(User *user);
	void demoteChanop(User *user);
	void promoteVoiceOp(User *user);
	void demoteVoiceOp(User *user);

	const string getTopic() const;
	void setTopic(string& arg);

	static bool isValidIdentifier(const string& identifier);
};

#endif /* FT_IRC_API_CHANNEL */
