#ifndef FT_IRC_API_PLUGIN
#define FT_IRC_API_PLUGIN

class Plugin {
public:
	virtual void onStart() = 0;
	virtual void onStop() = 0;
};

#endif /* FT_IRC_API_PLUGIN */
