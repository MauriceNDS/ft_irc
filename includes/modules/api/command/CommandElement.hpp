#ifndef FT_IRC_API_COMMAND_ELEMENT
#define FT_IRC_API_COMMAND_ELEMENT

#include <exception>

#include "ft_irc.hpp"

#include "api/ResponseType.hpp"

#include "api/event/MessageEvent.hpp"

class CommandElement {
public:
	virtual bool isRequired() const;

	virtual void *parseValue(const string& arg, MessageEvent& event) const = 0;

	virtual void destroy(void *) const;

	virtual ResponseType notProvidedResponse() const;

	virtual ~CommandElement();

	class Builder {
	private:
		CommandElement *_subtype;
		ResponseType _ifNotProvided;

	public:
		Builder();

		Builder& ifNotProvided(ResponseType response);
		Builder& element(CommandElement *element);
		CommandElement *build() const;
	};
};

class ComplexeCommandElement : public CommandElement {
private:
	friend class CommandElement::Builder;

	CommandElement *subtype;
	ResponseType ifNotProvided;
	ComplexeCommandElement(CommandElement *subtype, ResponseType ifNotProvided);
public:
	void *parseValue(const string& arg, MessageEvent& event) const;
	ResponseType notProvidedResponse() const;
	void destroy(void *arg) const;
	~ComplexeCommandElement();
};

#endif /* FT_IRC_API_COMMAND_ELEMENT */
