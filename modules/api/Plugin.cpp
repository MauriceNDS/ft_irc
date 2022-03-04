#include "api/Plugin.hpp"

void Plugin::construct() {};
void Plugin::preInit() {};
void Plugin::init() {};
void Plugin::postInit() {};
void Plugin::serverAboutToStart() {};
void Plugin::serverStarted() {};
void Plugin::serverStopping() {};
void Plugin::serverStopped() {};

Plugin::~Plugin() {};