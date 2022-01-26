#ifndef FT_IRC_API_COMMAND_ELEMENT
#define FT_IRC_API_COMMAND_ELEMENT

#include <exception>

#include "ft_irc.hpp"

#include "api/ResponseTypes.hpp"

#include "api/event/MessageEvent.hpp"

class CommandElement {
public:
	virtual bool isRequired() const;

	virtual void *parseValue(const string& arg, MessageEvent& event) const = 0;

	virtual void destroy(void *) const;

	virtual const ResponseSpec& notProvidedResponse() const;

	virtual ~CommandElement();

	class Builder {
	private:
		CommandElement *_subtype;
		const ResponseSpec *_ifNotProvided;

	public:
		Builder();

		Builder& ifNotProvided(const ResponseSpec& response);
		Builder& element(CommandElement *element);
		CommandElement *build() const;
	};
};

class ComplexeCommandElement : public CommandElement {
private:
	friend class CommandElement::Builder;

	CommandElement *subtype;
	const ResponseSpec& ifNotProvided;
	ComplexeCommandElement(CommandElement *subtype, const ResponseSpec& ifNotProvided);
public:
	void *parseValue(const string& arg, MessageEvent& event) const;
	const ResponseSpec& notProvidedResponse() const;
	void destroy(void *arg) const;
	~ComplexeCommandElement();
};

#endif /* FT_IRC_API_COMMAND_ELEMENT */
