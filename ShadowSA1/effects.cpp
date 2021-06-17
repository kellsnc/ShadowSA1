#include "pch.h"

static Trampoline* Sonic_Display_t = nullptr;
static NJS_OBJECT* ShadowAir_Object = nullptr;
static int NodeCount = 0;

void __cdecl Air_CallBack(NJS_MODEL_SADX* model, int a2, int a3)
{
	switch (NodeCount)
	{
	case 23:
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
		break;
	case 24:
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
		break;
	case 18:
		DrawModel_QueueVisible(ShadowAir_Object->child->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
		break;
	case 19:
		DrawModel_QueueVisible(ShadowAir_Object->child->sibling->sibling->sibling->basicdxmodel, (QueuedModelFlagsB)0, 1.0f);
		break;
	}

	NodeCount += 1;
}

void DrawShadowAir(EntityData1* data1, NJS_ACTION* action, Float frame)
{
	NodeCount = 0;

	njPushMatrixEx();
	njSetTexture(&SONIC_TEXLIST);
	njTranslateEx(&data1->CollisionInfo->CollisionArray->center);
	njRotateZ(0, data1->Rotation.z);
	njRotateX(0, data1->Rotation.x);
	njRotateY(0, -0x8000 - data1->Rotation.y);
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0.0f, Air_CallBack);
	njPopMatrixEx();
}

void Sonic_Display_r(ObjectMaster* obj)
{
	// Call original
	((decltype(Sonic_Display_r)*)Sonic_Display_t->Target())(obj);

	EntityData2* data2 = (EntityData2*)obj->Data2;
	CharObj2* co2 = data2->CharacterData;

	// Draw air on specific animations
	if (co2->AnimationThing.State == 2)
	{
		if (co2->AnimationThing.action == SONIC_ACTIONS[5] || co2->AnimationThing.action == SONIC_ACTIONS[6] || co2->AnimationThing.action == SONIC_ACTIONS[18])
		{
			DrawShadowAir(obj->Data1, co2->AnimationThing.action, co2->AnimationThing.Frame);
		}
	}
	else
	{
		if (co2->AnimationThing.Index == 11 || co2->AnimationThing.Index == 12 || co2->AnimationThing.Index == 13)
		{
			DrawShadowAir(obj->Data1, co2->AnimationThing.AnimData[co2->AnimationThing.Index].Animation, co2->AnimationThing.Frame);
		}
	}
}

void Effects_Init(const char* path, const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SHADOW_AIR.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic)
	{
		ShadowAir_Object = mdl->getmodel();

		if (ShadowAir_Object)
		{
			Sonic_Display_t = new Trampoline((int)Sonic_Display, (int)Sonic_Display + 0x7, Sonic_Display_r);
		}
	}
	else
	{
		PrintDebug("[Shadow SA1] Cannot open \"SHADOW_AIR.sa1mdl\".\n");
	}
}