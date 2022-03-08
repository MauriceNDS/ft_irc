#ifndef FT_IRC_API_CHANNEL
#define FT_IRC_API_CHANNEL

#include "ft_irc.hpp"

#include "api/interface/CommandSender.hpp"
#include "api/Group.hpp"

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

class Channel : public CommandSender, public Group {
private:
	string topic;
	set<User *> voiceop;
	set<User *> invite;
	Modes flags;

	Channel(const string& name);

public:
	static Channel *create(const string& name);
	~Channel();
	
	const string& getPassword() const;
	void setPassword(const string& password);

	// CommandSender
	string getName() const;
	string getSenderName() const;
	void send(const string& message) const;
	void send(const CommandSender& sender, const string& message) const;

	// Channel
	string getDisplayName(const User& user) const;

	const string getTopic() const;
	void setTopic(string& arg);

	const Modes& getFlags() const;
	Modes& getFlags();
	string getSymbol() const;

	bool isVoiceOp(const User &user) const;
	void promoteVoiceOp(User &user);
	void demoteVoiceOp(User &user);

	const set<User *>& getInvites() const;
	bool isInvited(User& user) const;
	void addInvite(User& user);

	// Listeners
	virtual void onJoin(GroupJoinEvent::Before& event);
	virtual void onJoin(GroupJoinEvent::After& event);
	virtual void onLeave(GroupLeaveEvent& event);

	static bool isValidIdentifier(const string& identifier);
};

#endif /* FT_IRC_API_CHANNEL */
