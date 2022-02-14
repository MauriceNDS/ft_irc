#ifndef FT_IRC_API_FLAGS_COMMAND_ELEMENT
#define FT_IRC_API_FLAGS_COMMAND_ELEMENT

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/ResponseTypes.hpp"
#include "api/Flag.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/command/CommandElement.hpp"
#include "api/event/MessageEvent.hpp"

class FlagsCommandElement : public CommandElement {
private:
	string flags;

public:
	FlagsCommandElement(const string& flags) : flags(flags) {}

	void *parseValues(list<string>& args, MessageEvent& event) const {
		vector<Flag> *modes = new vector<Flag>();
		modes->reserve(flags.length());

		while (!args.empty() && (args.front()[0] == '+' || args.front()[0] == '-')) {
			string current = args.front();
			args.pop_front();
			char sign = current[0];
			current.erase(current.begin());

			for (string::iterator it = current.begin(); it != current.end(); it++) {
				size_t pos = flags.find_first_of(*it);
				if (*it != ':' && pos != string::npos) {
					Flag flag(sign, *it);

					if (flags[pos + 1] == ':') {
						if (args.empty()) {
							event.getSender().send(ResponseTypes::ERR_NEEDMOREPARAMS("MODE"));
							destroy(modes);
							return NULL;
						}
						flag.value = args.front();
						args.pop_front();
					}
					modes->push_back(flag);
				} else {
					event.getSender().send(ResponseTypes::ERR_UNKNOWNMODE(string(1, *it).c_str()));
					destroy(modes);
					return NULL;
				}
			}
		}
		return modes;
	}

	void destroy(void *arg) const {
		delete static_cast<vector<Flag> *>(arg);
	}
};

#endif /* FT_IRC_API_FLAGS_COMMAND_ELEMENT */
