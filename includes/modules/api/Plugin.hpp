#ifndef FT_IRC_API_PLUGIN
#define FT_IRC_API_PLUGIN

#include "core/Irc.hpp"

#define PLUGIN(clazz) extern "C" Plugin *getPlugin() { return new clazz(); }

class Plugin {
public:
	virtual void construct() {};
	virtual void preInit() {};
	virtual void init() {};
	virtual void postInit() {};
	virtual void serverAboutToStart() {};
	virtual void serverStopping() {};
	virtual void serverStopped() {};

	virtual ~Plugin() {};
};

#endif /* FT_IRC_API_PLUGIN */
