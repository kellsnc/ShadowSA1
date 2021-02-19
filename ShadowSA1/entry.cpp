#include "pch.h"

void Tornado_init(const HelperFunctions& helperFunctions);

void SetLSDColor() {
	SetMaterialAndSpriteColor_Float(0.8f, 0.96f, 0.4f, 0.f);
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		// Resize sonic's texlist, fixes initialization with testspawn.
		SONIC_TEXLIST.nbTexture = 14;

		// Disable shoe morphs
		WriteData<3>((void*)0x493722, 0x90);
		WriteData<3>((void*)0x4936EA, 0x90);
		WriteData<3>((void*)0x493657, 0x90);
		WriteData<3>((void*)0x4936CD, 0x90);
		WriteData<3>((void*)0x493C5D, 0x90);
		WriteData<3>((void*)0x4937A1, 0x90);
		WriteData<3>((void*)0x4937A1, 0x90);

		WriteCall((void*)0x4A1705, SetLSDColor);

		if (config->getBool("", "Tornado", true)) {
			Tornado_init(helperFunctions);
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}