#ifndef FT_IRC_API_COMMAND_ELEMENT
#define FT_IRC_API_COMMAND_ELEMENT

#include <exception>

#include "ft_irc.hpp"

#include "server/Response.hpp"

#include "api/event/MessageEvent.hpp"

class CommandElement {
public:
	virtual bool isRequired() const;

	virtual void *parseValue(const string& arg, MessageEvent& event) const = 0;

	virtual void destroy(void *) const;

	virtual Response notProvidedResponse() const;

	virtual ~CommandElement();

	class Builder {
	private:
		CommandElement *_subtype;
		Response _ifNotProvided;

	public:
		Builder();

		Builder& ifNotProvided(Response response);
		Builder& element(CommandElement *element);
		CommandElement *build() const;
	};
};

class ComplexeCommandElement : public CommandElement {
private:
	friend class CommandElement::Builder;

	CommandElement *subtype;
	Response ifNotProvided;
	ComplexeCommandElement(CommandElement *subtype, Response ifNotProvided);
public:
	void *parseValue(const string& arg, MessageEvent& event) const;
	Response notProvidedResponse() const;
	void destroy(void *arg) const;
	~ComplexeCommandElement();
};

#endif /* FT_IRC_API_COMMAND_ELEMENT */
