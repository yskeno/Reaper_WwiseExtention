// Reaper_WwiseExtention.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Reaper_WwiseExtention.h"


// Actions

static custom_action_register_t actReg_ =
{
	static_cast<int>(ActionsList::Main),	// Section
	"YSKENO_WWISE_EXTENTION",	// ActionID(Must be Unique)
	"Wwise Extention : Open Window",	// Description
	0,	// reserved
};

static int actionID_ = 0;

gaccel_register_t actionOpenTransferWindow = { {0, 0, 0}, "Open WAAPI transfer window." };

// Actions
static bool HookCommand2(KbdSectionInfo* sec, int command, int val, int valhw, int relmode, HWND hwnd)
{
	if (sec->uniqueID != actReg_.uniqueSectionId || command != actionID_)
		return false;

	ShowConsoleMsg("Hello Wwise Extention!");
	return true;
}


// Extention Menu
void HookCustomMenu(const char* menustr, HMENU hMenu, int flag)
{
	if (0 == flag && 0 == strcmp(menustr, "Main extensions"))
	{
		MENUITEMINFO mi = { sizeof(MENUITEMINFO), };
		mi.fMask = MIIM_TYPE | MIIM_ID;
		mi.fType = MFT_STRING;
		mi.wID = actionID_;
		mi.dwTypeData = L"Wwise Extention";
		InsertMenuItem(hMenu, 0, true, &mi);
	}
}


extern "C"
{
	REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE hInstance, reaper_plugin_info_t* rec)
	{
		if (!rec)
		{
			//Unregister from Actions & Extension Menu.
			plugin_register("-custom_action", &actReg_);
			plugin_register("-hookcommand2", HookCommand2);
			plugin_register("-hookcustommenu", (void*)HookCustomMenu);

			return 0;
		}
		else
		{
			// Loading extention
			int numOfErrors = REAPERAPI_LoadAPI(rec->GetFunc);

			// Register Callback for run Actions & Extention Menu.
			plugin_register("hookcommand2", HookCommand2);
			plugin_register("hookcustommenu", (void*)HookCustomMenu);
			actionID_ = plugin_register("custom_action", &actReg_);

			AddExtensionsMainMenu();
			HMENU hMenu = GetSubMenu(GetMenu(GetMainHwnd()), 0);
			{
				MENUITEMINFO mi = { sizeof(MENUITEMINFO), };
				mi.fMask = MIIM_TYPE | MIIM_ID;
				mi.fType = MFT_STRING;
				mi.wID = actionID_;
				mi.dwTypeData = L"Wwise Extention";
				InsertMenuItem(hMenu, 0, true, &mi);
			}


			return 1;
		}
	}
}