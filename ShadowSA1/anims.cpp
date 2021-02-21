#include "pch.h"

void ReplaceAnims(const char* path) {
	AnimationFile* anm5 = new AnimationFile((std::string)path + "\\CHRMODELS\\___SONIC_ACTIONS\\005.saanim");
	AnimationFile* anm6 = new AnimationFile((std::string)path + "\\CHRMODELS\\___SONIC_ACTIONS\\006.saanim");
	AnimationFile* anm18 = new AnimationFile((std::string)path + "\\CHRMODELS\\___SONIC_ACTIONS\\018.saanim");

	HMODULE hm = GetModuleHandle(L"CHRMODELS_orig");
	NJS_ACTION** SONIC_ACTIONS = (NJS_ACTION**)GetProcAddress(hm, "___SONIC_ACTIONS");

	if (SONIC_ACTIONS) {
		SONIC_ACTIONS[5]->motion = anm5->getmotion();
		SONIC_ACTIONS[6]->motion = anm6->getmotion();
		SONIC_ACTIONS[18]->motion = anm18->getmotion();
	}
}

void InitShadowAnimData();
Trampoline InitSonicAnimData_t((int)InitSonicAnimData, (int)InitSonicAnimData + 0x5, InitShadowAnimData);
void InitShadowAnimData() {
	VoidFunc(original, InitSonicAnimData_t.Target());
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