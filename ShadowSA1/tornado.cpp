#include "pch.h"

static ModelInfo* ShadowPlaneMdl = nullptr;

DataPointer(NJS_OBJECT, Tornado1_Object, 0x28B1DA0);
DataPointer(NJS_OBJECT, Tornado2Before_Object, 0x27EB198);
DataPointer(NJS_OBJECT, Tornado2Change_Object, 0x280C158);

static bool CheckIfShadowPlane(NJS_MODEL_SADX* model)
{
	return ShadowPlaneMdl->getlabel(model) != "";
}

static void __cdecl TornadoCallBack(NJS_MODEL_SADX* model, int blend, int idk)
{
	NonStaticFunctionPointer(void, sub_407FC0, (NJS_MODEL_SADX*, int), 0x407FC0);

	// If the currently drawn model is part of SHADOW_PLANE, we use the character's texlist instead
	if (CheckIfShadowPlane(model))
	{
		NJS_TEXLIST* tex_orig = CurrentTexList;

		njSetTexture(&SONIC_TEXLIST);
		sub_407FC0(model, blend);
		njSetTexture(tex_orig);
	}
	else
	{
		sub_407FC0(model, blend);
	}
}

static void __cdecl njAction_Queue_Tornado(NJS_ACTION* action, float frame, QueuedModelFlagsB flags)
{
	DisplayAnimationFrame(action, frame, flags, 0.0, TornadoCallBack);
}

void Tornado_init()
{
	ShadowPlaneMdl = OpenModel("SHADOW_PLANE.sa1mdl");

	if (ShadowPlaneMdl)
	{
		NJS_OBJECT* model = ShadowPlaneMdl->getmodel();

		if (model)
		{
			// We only replace Sonic's part of the plane
			Tornado1_Object.child->sibling->sibling->sibling->child = model;
			Tornado2Before_Object.child->sibling->sibling->child = model;
			Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = model;

			// Hack to use our own texture for Shadow's part of the plane, allowing compatibility with dc mods.
			WriteCall((void*)0x62753A, njAction_Queue_Tornado);
		}
	}
}