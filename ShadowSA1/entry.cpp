#include "pch.h"

void ReplaceAnims(const char* path);
void Tornado_init(const HelperFunctions& helperFunctions);

DataPointer(NJS_OBJECT, SonicPointingHand_Object, 0x2DD8708);

void SetLSDColor() {
	SetMaterialAndSpriteColor_Float(0.8f, 0.96f, 0.4f, 0.f);
}

void PointingFinger_Init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SHADOW_POINTINGHAND.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPointingHand_Object = *mdl->getmodel();
	}
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

		// Replace the light speed dash aura color
		WriteCall((void*)0x4A1705, SetLSDColor);

		// Replace the pointing finger model that's used in cutscenes
		PointingFinger_Init(helperFunctions);

		// Because the ini replacement doesn't work
		ReplaceAnims(path);

		// Replace low-poly Sonic on the Tornado by low-poly Shadow
		if (config->getBool("", "Tornado", true)) {
			Tornado_init(helperFunctions);
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}