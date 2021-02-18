#include "pch.h"

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		// Disable shoe morphs
		WriteData<3>((void*)0x493722, 0x90);
		WriteData<3>((void*)0x4936EA, 0x90);
		WriteData<3>((void*)0x493657, 0x90);
		WriteData<3>((void*)0x4936CD, 0x90);
		WriteData<3>((void*)0x493C5D, 0x90);
		WriteData<3>((void*)0x4937A1, 0x90);
		WriteData<3>((void*)0x4937A1, 0x90);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}