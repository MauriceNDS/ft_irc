#ifndef FT_IRC_API_CANCELLABLE
#define FT_IRC_API_CANCELLABLE

class Cancellable {
protected:
	bool cancelled;

public:
	explicit Cancellable(bool value = false);
	virtual ~Cancellable() = 0;

	void setCancelled(bool cancel);
	bool isCancelled() const;
};

#endif /* FT_IRC_API_CANCELLABLE */
