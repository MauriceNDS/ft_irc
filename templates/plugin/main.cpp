#include "myplugin.hpp"

PLUGIN(MyPlugin, "myplugin")

void MyPlugin::construct() {
	irc = &Irc::getInstance();
}
