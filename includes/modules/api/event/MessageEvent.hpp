#ifndef FT_IRC_API_MESSAGE_EVENT
#define FT_IRC_API_MESSAGE_EVENT

#include "api/Client.hpp"
#include "api/event/Cancellable.hpp"

class MessageEvent : public Cancellable {
private:
	string message;
	Client& sender;

public:
	MessageEvent(const string& message, Client& sender);

	Client& getSender() const;

	const string& getMessage() const;

	void setCancelled(bool cancel);
	
	bool isCancelled() const;
};

#endif /* FT_IRC_API_MESSAGE_EVENT */
