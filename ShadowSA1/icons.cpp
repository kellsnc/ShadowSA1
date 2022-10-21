#include "pch.h"
#include "SADXModLoader.h"
#include "FunctionHook.h"
#include "icons.h"

FunctionHook<void, int> LoadTextureForEachGameMode_h(0x4212E0);
FunctionHook<void> ReleaseTextureForEachGameMode_h(0x420F40);

static NJS_TEXNAME SHADOW_EXTRA_TEXNAME[8] = {};
static NJS_TEXLIST SHADOW_EXTRA_TEXLIST = { arrayptrandlengthT(SHADOW_EXTRA_TEXNAME, int) };

static void __cdecl LoadTextureForEachGameMode_r(int gamemode)
{
	// Load textures with the same global index as others from CON_REGULAR and OBJ_REGULAR beforehand to soft-replace them.
	LoadPVM("SHADOW_EXTRA", &SHADOW_EXTRA_TEXLIST);
	LoadTextureForEachGameMode_h.Original(gamemode);
}

static void __cdecl ReleaseTextureForEachGameMode_r()
{
	njReleaseTexture(&SHADOW_EXTRA_TEXLIST);
	ReleaseTextureForEachGameMode_h.Original();
}

void Icons_Init()
{
	LoadTextureForEachGameMode_h.Hook(LoadTextureForEachGameMode_r);
	ReleaseTextureForEachGameMode_h.Hook(ReleaseTextureForEachGameMode_r);
}
