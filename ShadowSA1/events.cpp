#include "pch.h"

void __cdecl Sonic_Main_r(ObjectMaster* obj);
Trampoline Sonic_Main_t((int)Sonic_Main, (int)Sonic_Main + 0x7, Sonic_Main_r);
void __cdecl Sonic_Main_r(ObjectMaster* obj) {
	// Prevent Sonic's cinematic head from appearing
	SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling = SONIC_OBJECTS[46];

	NonStaticFunctionPointer(void, original, (ObjectMaster* obj), Sonic_Main_t.Target());
	original(obj);
};

void __cdecl sub_4310D0_r(ObjectMaster* obj, const char* list);
Trampoline sub_4310D0_t(0x4310D0, 0x4310D6, sub_4310D0_r);
void __cdecl sub_4310D0_r(ObjectMaster* obj, const char* list) {
	NonStaticFunctionPointer(void, original, (ObjectMaster * obj, const char* list), sub_4310D0_t.Target());
	
	if (obj->Data1->CharID != Characters_Sonic) {
		original(obj, list);
	}
};