#include "myplugin.hpp"

PLUGIN(MyPlugin)

void MyPlugin::construct() {
	irc = &Irc::getInstance();
}
