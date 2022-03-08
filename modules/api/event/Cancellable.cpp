#include "api/event/Cancellable.hpp"

Cancellable::Cancellable(bool value) : cancelled(value) {}
Cancellable::~Cancellable() {}

void Cancellable::setCancelled(bool cancel) {
	this->cancelled = cancel;
}

bool Cancellable::isCancelled() const {
	return this->cancelled;
}
