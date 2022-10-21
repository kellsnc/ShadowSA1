#include "pch.h"
#include "config.h"
#include "icons.h"
#include "tornado.h"
#include "effects.h"
#include "chrmodels.h"

static void __cdecl SetLSDColor()
{
	SetMaterial(0.8f, 0.96f, 0.4f, 0.0f);
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		config::init(path);

		// Replace Sonic stuff in CHRMODELS.DLL
		HookCHRMODELS();

		// Replace life icon and itemboxes 1up icon
		if (config::bIcons)
		{
			Icons_Init();
		}

		// Air effect under shoes
		if (config::bAirEffects)
		{
			Effects_Init();
		}

		// Replace low-poly Sonic on the Tornado by low-poly Shadow
		if (config::bTornadoHack)
		{
			Tornado_init();
		}

		// Resize sonic's texlist, fixes initialization with testspawn.
		SONIC_TEXLIST.nbTexture = 14;

		// Disable shoe morphs
		WriteData<1>((void*)0x493500, 0xC3);

		// Replace the light speed dash aura color
		WriteCall((void*)0x4A1705, SetLSDColor);

		helperFunctions.ReplaceFile("system\\SONIC.pvm", "system\\SHADOW_DC.pvm");
		helperFunctions.ReplaceFile("system\\SUPERSONIC.pvm", "system\\SUPERSHADOW_DC.pvm");
		helperFunctions.ReplaceFile("system\\SON_EFF.pvm", "system\\SHADOW_EFF_DC.pvm");
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}