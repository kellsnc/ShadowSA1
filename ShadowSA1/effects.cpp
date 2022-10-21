#include "pch.h"
#include "SADXModLoader.h"
#include "FunctionHook.h"
#include "utils.h"
#include "effects.h"

FunctionHook<void, task*> Sonic_Display_h(0x4948C0);
static NJS_OBJECT* ShadowAir_Object = nullptr;
static int NodeCount = 0;

static void __cdecl Air_CallBack(NJS_MODEL_SADX* model, int, int)
{
	switch (NodeCount)
	{
	case 23:
		late_DrawModel(ShadowAir_Object->child->sibling->basicdxmodel, LATE_MAT);
		break;
	case 24:
		late_DrawModel(ShadowAir_Object->child->sibling->sibling->basicdxmodel, LATE_MAT);
		break;
	case 18:
		late_DrawModel(ShadowAir_Object->child->basicdxmodel, LATE_MAT);
		break;
	case 19:
		late_DrawModel(ShadowAir_Object->child->sibling->sibling->sibling->basicdxmodel, LATE_MAT);
		break;
	}

	NodeCount += 1;
}

static void DrawShadowAir(taskwk* twp, NJS_ACTION* action, float frame)
{
	NodeCount = 0;

	njPushMatrixEx();
	njSetTexture(&SONIC_TEXLIST);
	njTranslateEx(&twp->cwp->info->center);
	njRotateZ(0, twp->ang.z);
	njRotateX(0, twp->ang.x);
	njRotateY(0, -0x8000 - twp->ang.y);
	DrawAction(action, frame, LATE_MAT, 0.0f, Air_CallBack);
	njPopMatrixEx();
}

static void Sonic_Display_r(task* tp)
{
	Sonic_Display_h.Original(tp);

	auto twp = tp->twp;
	auto pwp = (playerwk*)tp->mwp->work.ptr;

	// Draw air on specific animations

	if (pwp->mj.mtnmode == 2)
	{
		if (pwp->mj.action == 11 || pwp->mj.action == 12 || pwp->mj.action == 13)
		{
			DrawShadowAir(twp, pwp->mj.actwkptr, pwp->mj.nframe);
		}
	}
	else
	{
		if (pwp->mj.reqaction == 11 || pwp->mj.reqaction == 12 || pwp->mj.reqaction == 13)
		{
			DrawShadowAir(twp, pwp->mj.plactptr[pwp->mj.reqaction].actptr, pwp->mj.nframe);
		}
	}
}

void Effects_Init()
{
	auto mdl = OpenModel("SHADOW_AIR.sa1mdl");

	if (mdl)
	{
		ShadowAir_Object = mdl->getmodel();

		if (ShadowAir_Object)
		{
			Sonic_Display_h.Hook(Sonic_Display_r);
		}
	}
}
