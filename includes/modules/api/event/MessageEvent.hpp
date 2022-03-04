#ifndef FT_IRC_API_MESSAGE_EVENT
#define FT_IRC_API_MESSAGE_EVENT

#include "api/Client.hpp"

class MessageEvent {
private:
	string message;
	Client& sender;
	bool cancelled;

public:
	MessageEvent(const string& message, Client& sender);

	Client& getSender() const;

	const string& getMessage() const;

	void setCancelled(bool cancel);
	
	bool isCancelled() const;
};

#endif /* FT_IRC_API_MESSAGE_EVENT */
