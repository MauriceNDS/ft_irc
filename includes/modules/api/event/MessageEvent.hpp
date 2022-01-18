#ifndef FT_IRC_API_MESSAGE_EVENT
#define FT_IRC_API_MESSAGE_EVENT

#include "api/Client.hpp"

class MessageEvent {
private:
	string message;
	Client& sender;
	bool cancelled;

public:
	MessageEvent(const string& message, Client& sender) : message(message), sender(sender), cancelled(false) {}

	Client& getSender() const {
		return this->sender;
	}

	const string& getMessage() const {
		return this->message;
	}

	void setCancelled(bool cancel) {
		this->cancelled = cancel;
	}
	
	bool isCancelled() const {
		return this->cancelled;
	}
};

#endif /* FT_IRC_API_MESSAGE_EVENT */