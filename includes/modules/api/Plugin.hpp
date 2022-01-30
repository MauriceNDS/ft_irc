#ifndef FT_IRC_API_PLUGIN
#define FT_IRC_API_PLUGIN

#include "core/Irc.hpp"

#define PLUGIN(clazz) extern "C" Plugin *getPlugin() { return new clazz(); }

class Plugin {
public:
	virtual void onStart(Irc& irc) = 0;
	virtual void onStop() = 0;
};

#endif /* FT_IRC_API_PLUGIN */
