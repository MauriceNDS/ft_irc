#ifndef FT_IRC_API_PLUGIN
#define FT_IRC_API_PLUGIN

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#define PLUGIN(clazz, id) extern "C" Plugin *getPlugin() { return new clazz(); } string clazz::getId() const { return id; }

class Plugin {
public:
	virtual string getId() const = 0;

	virtual void construct() {};
	virtual void preInit() {};
	virtual void init() {};
	virtual void postInit() {};
	virtual void serverAboutToStart() {};
	virtual void serverStarted() {};
	virtual void serverStopping() {};
	virtual void serverStopped() {};

	virtual ~Plugin() {};
};

#endif /* FT_IRC_API_PLUGIN */
