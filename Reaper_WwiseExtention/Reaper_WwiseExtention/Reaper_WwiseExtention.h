//#include <cstdint>
#include <cstring>

#define REAPERAPI_IMPLEMENT
#include "reaper_plugin_functions.h"
#include "reaper_plugin.h"

// Actions
enum class ActionsList
{
	Main = 0,
	MainAlt = 100,
	MIDIEditor = 32060,
	MIDIEventList = 32061,
	MIDIInlineEditor = 32062,
	MediaExplorer = 32063,
};