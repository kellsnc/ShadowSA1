#include "pch.h"

void Tornado_init(const HelperFunctions& helperFunctions);
void Effects_Init(const char* path, const HelperFunctions& helperFunctions);

DataPointer(NJS_OBJECT, SonicPointingHand_Object, 0x2DD8708);

static NJS_TEXNAME HYOJI_ZANKI_S_TEXNAME = {};
static NJS_TEXLIST SHADOW_EXTRA_TEXLIST = { &HYOJI_ZANKI_S_TEXNAME, 1 };

void SetLSDColor()
{
	SetMaterialAndSpriteColor_Float(0.8f, 0.96f, 0.4f, 0.f);
}

void PointingFinger_Init(const HelperFunctions& helperFunctions)
{
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SHADOW_POINTINGHAND.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic)
	{
		SonicPointingHand_Object = *mdl->getmodel();
	}
}

Trampoline* LoadRegObjTextures_t = nullptr;
void __cdecl LoadRegObjTextures_r(int a1)
{
	// Load textures with the same global index as others from CON_REGULAR and OBJ_REGULAR beforehand to soft-replace them.
	LoadPVM("SHADOW_EXTRA", &SHADOW_EXTRA_TEXLIST);
	((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_t->Target())(a1);
}

Trampoline* FreeRegObjTexlists_t = nullptr;
void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&SHADOW_EXTRA_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_t->Target())();
}

ModelInfo* MorphHeadModel = nullptr;

void ReplaceMorphHead()
{
	SONIC_MODELS[9] = MorphHeadModel->getmodel()->basicdxmodel;
	SONIC_MODELS[8] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->basicdxmodel;

	SONIC_MODELS_9 = SONIC_MODELS[9];
	SONIC_MODELS_8 = SONIC_MODELS[8];
	SONIC_MODELS_9B = SONIC_MODELS[9];
	SONIC_MODELS_8B = SONIC_MODELS[8];
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		if (config->getBool("", "Icon", true))
		{
			LoadRegObjTextures_t = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
			FreeRegObjTexlists_t = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
		}

		// Resize sonic's texlist, fixes initialization with testspawn.
		SONIC_TEXLIST.nbTexture = 14;

		// Morph Head stuff because Mod Loader has trouble
		std::string model_path = (std::string)path + "\\CHRMODELS\\___SONIC_MODELS\\009.sa1mdl";
		MorphHeadModel = new ModelInfo(model_path.c_str());
		WriteJump((void*)0x7D0B20, ReplaceMorphHead);

		// Disable shoe morphs
		WriteData<1>((void*)0x493500, 0xC3);

		// Replace the light speed dash aura color
		WriteCall((void*)0x4A1705, SetLSDColor);

		// Replace the pointing finger model that's used in cutscenes
		PointingFinger_Init(helperFunctions);

		// Air effect under shoes
		if (config->getBool("", "Air", true))
		{
			Effects_Init(path, helperFunctions);
		}
		
		// Replace low-poly Sonic on the Tornado by low-poly Shadow
		if (config->getBool("", "Tornado", true))
		{
			Tornado_init(helperFunctions);
		}

		delete config;
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}