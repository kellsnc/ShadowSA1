#include "pch.h"

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}