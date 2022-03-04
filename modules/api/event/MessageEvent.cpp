#include "api/event/MessageEvent.hpp"

MessageEvent::MessageEvent(const string& message, Client& sender) : message(message), sender(sender), cancelled(false) {}

Client& MessageEvent::getSender() const {
	return this->sender;
}

const string& MessageEvent::getMessage() const {
	return this->message;
}

void MessageEvent::setCancelled(bool cancel) {
	this->cancelled = cancel;
}

bool MessageEvent::isCancelled() const {
	return this->cancelled;
}