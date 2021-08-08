#include "pch.h"

static Trampoline* LoadRegObjTextures_t = nullptr;
static Trampoline* FreeRegObjTexlists_t = nullptr;

static NJS_TEXNAME SHADOW_EXTRA_TEXNAME[2] = {};
static NJS_TEXLIST SHADOW_EXTRA_TEXLIST = { arrayptrandlengthT(SHADOW_EXTRA_TEXNAME, int) };

static void __cdecl LoadRegObjTextures_r(int a1)
{
	// Load textures with the same global index as others from CON_REGULAR and OBJ_REGULAR beforehand to soft-replace them.
	LoadPVM("SHADOW_EXTRA", &SHADOW_EXTRA_TEXLIST);
	((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_t->Target())(a1);
}

static void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&SHADOW_EXTRA_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_t->Target())();
}

void Icons_Init()
{
	LoadRegObjTextures_t = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
	FreeRegObjTexlists_t = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
}