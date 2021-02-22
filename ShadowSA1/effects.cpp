#include "pch.h"

static NJS_OBJECT* ShadowAir_Object = nullptr;
static int NodeCount = 0;

void __cdecl Air_CallBack(NJS_MODEL_SADX* model, int a2, int a3) {
	if (NodeCount == 23) {
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
	}
	else if (NodeCount == 24) {
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
	}
	else if (NodeCount == 18) {
		DrawModel_QueueVisible(ShadowAir_Object->child->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
	}
	else if (NodeCount == 19) {
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->sibling->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
	}

	NodeCount += 1;
}

void Sonic_Display_r(ObjectMaster* obj);
Trampoline Sonic_Display_t((int)Sonic_Display, (int)Sonic_Display + 0x7, Sonic_Display_r);
void Sonic_Display_r(ObjectMaster* obj) {
	NonStaticFunctionPointer(void, original, (ObjectMaster * obj), Sonic_Display_t.Target());
	original(obj);

	if (ShadowAir_Object) {
		EntityData1* data1 = obj->Data1;
		EntityData2* data2 = (EntityData2*)obj->Data2;
		CharObj2* co2 = data2->CharacterData;
		
		if (co2->AnimationThing.Index == 11 || co2->AnimationThing.Index == 12 || co2->AnimationThing.Index == 13) {
			NodeCount = 0;

			njPushMatrixEx();
			njSetTexture(&SONIC_TEXLIST);
			njTranslateEx(&data1->CollisionInfo->CollisionArray->center);
			njRotateZ(0, data1->Rotation.z);
			njRotateX(0, data1->Rotation.x);
			njRotateY(0, -0x8000 - data1->Rotation.y);
			DisplayAnimationFrame(co2->AnimationThing.AnimData[co2->AnimationThing.Index].Animation, co2->AnimationThing.Frame, (QueuedModelFlagsB)0, 0.0f, Air_CallBack);
			njPopMatrixEx();
		}
	}
}

void LoadAirModels(const char* path, const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SHADOW_AIR.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		ShadowAir_Object = mdl->getmodel();
	}
	else {
		PrintDebug("[Shadow SA1] Cannot open \"SHADOW_AIR.sa1mdl\".\n");
	}
}