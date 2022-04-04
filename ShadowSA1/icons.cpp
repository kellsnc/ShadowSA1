#include "pch.h"
#include "icons.h"

static Trampoline* LoadTextureForEachGameMode_t = nullptr;
static Trampoline* ReleaseTextureForEachGameMode_t = nullptr;

static NJS_TEXNAME SHADOW_EXTRA_TEXNAME[8] = {};
static NJS_TEXLIST SHADOW_EXTRA_TEXLIST = { arrayptrandlengthT(SHADOW_EXTRA_TEXNAME, int) };

static void __cdecl LoadTextureForEachGameMode_r(int gamemode)
{
	// Load textures with the same global index as others from CON_REGULAR and OBJ_REGULAR beforehand to soft-replace them.
	LoadPVM("SHADOW_EXTRA", &SHADOW_EXTRA_TEXLIST);
	CALL_ORIGINAL(LoadTextureForEachGameMode)(gamemode);
}

static void __cdecl ReleaseTextureForEachGameMode_r()
{
	njReleaseTexture(&SHADOW_EXTRA_TEXLIST);
	CALL_ORIGINAL(ReleaseTextureForEachGameMode)();
}

void Icons_Init()
{
	LoadTextureForEachGameMode_t = new Trampoline(0x4212E0, 0x4212E5, LoadTextureForEachGameMode_r);
	ReleaseTextureForEachGameMode_t = new Trampoline(0x420F40, 0x420F45, ReleaseTextureForEachGameMode_r);
}