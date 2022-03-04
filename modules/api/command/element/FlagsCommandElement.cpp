#include "core/Irc.hpp"

#include "api/Flag.hpp"
#include "api/User.hpp"
#include "api/Channel.hpp"
#include "api/ResponseTypes.hpp"
#include "api/command/element/FlagsCommandElement.hpp"

FlagsCommandElement::FlagsCommandElement(const string& flags) : flags(flags) {}

void *FlagsCommandElement::parseValues(list<string>& args, MessageEvent& event) const {
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

				char next = flags[pos + 1];
				if (next == ':' || next == sign) {
					if (args.empty()) {
						event.getSender().send(ResponseTypes::ERR_NEEDMOREPARAMS("MODE"));
						destroy(modes);
						return NULL;
					}
					flag.has_value = true;
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

void FlagsCommandElement::destroy(void *arg) const {
	delete static_cast<vector<Flag> *>(arg);
}