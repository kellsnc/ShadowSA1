#include "pch.h"

DataArray(NJS_ACTION*, SonicCharSelActions, 0x3C5FF94, 4);

void __cdecl InitShadowAnimData();
Trampoline InitSonicAnimData_t((int)InitSonicAnimData, (int)InitSonicAnimData + 0x5, InitShadowAnimData);
void __cdecl InitShadowAnimData() {
	NonStaticFunctionPointer(void, original, (), InitSonicAnimData_t.Target());
	original();

	SonicAnimData[11].AnimationSpeed = 0.4f;
	SonicAnimData[11].TransitionSpeed = 0.5f;
	SonicAnimData[11].Property = 9;

	SonicAnimData[12].AnimationSpeed = 0.25f;
	SonicAnimData[12].TransitionSpeed = 0.25f;
	SonicAnimData[12].Property = 10;

	SonicAnimData[13].AnimationSpeed = 0.30f;
	SonicAnimData[13].TransitionSpeed = 0.25f;
	SonicAnimData[13].Property = 10;
}