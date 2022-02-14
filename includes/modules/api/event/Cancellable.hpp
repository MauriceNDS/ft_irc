#ifndef FT_IRC_API_CANCELLABLE
#define FT_IRC_API_CANCELLABLE

class Cancellable {
protected:
	bool cancelled;

public:
	void setCancelled(bool cancel) {
		this->cancelled = cancel;
	}
	
	bool isCancelled() const {
		return this->cancelled;
	}

	virtual ~Cancellable() = 0;
};

#endif /* FT_IRC_API_CANCELLABLE */
