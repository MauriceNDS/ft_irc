#ifndef MY_PLUGIN_HPP
#define MY_PLUGIN_HPP

#include "ft_irc.hpp"

#include "core/Irc.hpp"

#include "api/Plugin.hpp"

class MyPlugin : public Plugin {
private:
	Irc *irc;

public:
	string getId() const;

	void construct();
};

#endif /* MY_PLUGIN_HPP */
