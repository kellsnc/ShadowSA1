#include "pch.h"
#include "SADXModLoader.h"
#include "FunctionHook.h"
#include "config.h"
#include "utils.h"
#include "chrmodels.h"

DataArray(PL_JOIN_VERTEX, sonic_jv_list, 0x3C55E28, 37);
DataPointer(NJS_OBJECT, SonicPointingHand_Object, 0x2DD8708);

#define INIT_WELD(id, base, mdlA, mdlB, table) sonic_jv_list[id] = { SONIC_OBJECTS[base], SONIC_OBJECTS[mdlA], SONIC_OBJECTS[mdlB], static_cast<char>(LengthOfArray(table) / 2), PL_JOIN_SRC, 0, 0, nullptr, (uint16_t*)table }

static ModelInfo* SHADOW_OBJECT_000;
static ModelInfo* SHADOW_OBJECT_022;
static ModelInfo* SHADOW_OBJECT_044;
static ModelInfo* SHADOW_OBJECT_047;
static ModelInfo* SHADOW_OBJECT_054;
static ModelInfo* SHADOW_OBJECT_058;
static ModelInfo* SHADOW_OBJECT_060;
static ModelInfo* SHADOW_OBJECT_063;
static ModelInfo* SHADOW_OBJECT_064;
static ModelInfo* SHADOW_OBJECT_065;
static ModelInfo* SHADOW_OBJECT_066;
static ModelInfo* SHADOW_ACTION_142;
static ModelInfo* SHADOW_MODEL_009;
static AnimationFile* SHADOW_ACTION_005;
static AnimationFile* SHADOW_ACTION_006;
static AnimationFile* SHADOW_ACTION_018;
static AnimationFile* SHADOW_MOTION_000;

FunctionHook<void> InitSonicWeldInfo_h(0x7D0B50);
FunctionHook<void> InitSonicAnimData_h(0x7CEC90);

static const uint16_t Shadow_UpperArmIndices[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

static const uint16_t Shadow_LowerArmIndices[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

static const uint16_t Shadow_UpperLegIndices[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

static const uint16_t Shadow_LowerLegIndices[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

static const uint16_t Shadow_ShoeIndices[] = {
	33, 27,
	15, 12,
	14, 9,
	12, 7,
	10, 1,
	11, 2,
	3, 0
};

static const uint16_t Shadow_HandIndices[] = {
	4, 15,
	0, 14,
	1, 13,
	5, 12
};

static void __cdecl InitNPCSonicWeldInfo_r()
{
	memcpy(NPCSonicWeldInfo, SonicWeldInfo, sizeof(WeldInfo) * 15);
	NPCSonicWeldInfo[15] = {};
}

static void __cdecl InitSonicWeldInfo_r()
{
	// Call original to allow the game to initialize Metal Sonic welds.
	InitSonicWeldInfo_h.Original();

	// Sonic
	INIT_WELD(0, 0, 1, 2, Shadow_UpperArmIndices);
	INIT_WELD(1, 0, 2, 3, Shadow_LowerArmIndices);
	INIT_WELD(2, 0, 7, 8, Shadow_UpperArmIndices);
	INIT_WELD(3, 0, 8, 9, Shadow_LowerArmIndices);
	INIT_WELD(4, 0, 12, 13, Shadow_UpperLegIndices);
	INIT_WELD(5, 0, 13, 14, Shadow_LowerLegIndices);
	INIT_WELD(6, 0, 17, 18, Shadow_UpperLegIndices);
	INIT_WELD(7, 0, 18, 19, Shadow_LowerLegIndices);
	INIT_WELD(8, 0, 15, 16, Shadow_ShoeIndices);
	INIT_WELD(9, 0, 20, 21, Shadow_ShoeIndices);
	INIT_WELD(10, 0, 10, 11, Shadow_HandIndices);
	INIT_WELD(11, 0, 4, 5, Shadow_HandIndices);
	INIT_WELD(12, 0, 58, 59, Shadow_ShoeIndices); // Left shoe upgrade
	INIT_WELD(13, 0, 60, 61, Shadow_ShoeIndices); // Right shoe upgrade
	INIT_WELD(14, 0, 2, 63, Shadow_LowerArmIndices); // Wrist upgrade

	// Super Sonic
	INIT_WELD(22, 22, 23, 24, Shadow_UpperArmIndices);
	INIT_WELD(23, 22, 24, 25, Shadow_LowerArmIndices);
	INIT_WELD(24, 22, 28, 29, Shadow_UpperArmIndices);
	INIT_WELD(25, 22, 29, 30, Shadow_LowerArmIndices);
	INIT_WELD(26, 22, 33, 34, Shadow_UpperLegIndices);
	INIT_WELD(27, 22, 34, 35, Shadow_LowerLegIndices);
	INIT_WELD(28, 22, 38, 39, Shadow_UpperLegIndices);
	INIT_WELD(29, 22, 39, 40, Shadow_LowerLegIndices);
	INIT_WELD(30, 22, 36, 37, Shadow_ShoeIndices);
	INIT_WELD(31, 22, 41, 42, Shadow_ShoeIndices);
	INIT_WELD(32, 22, 31, 32, Shadow_HandIndices);
	INIT_WELD(33, 22, 26, 27, Shadow_HandIndices);
	INIT_WELD(34, 22, 31, 32, Shadow_HandIndices);
	INIT_WELD(35, 22, 26, 27, Shadow_HandIndices);
}

static void __cdecl InitSonicAnimData_r()
{
	// Call original to allow the game to initialize the other animation
	InitSonicAnimData_h.Original(),

	sonic_action[11].frame = 0.4f;
	sonic_action[11].racio = 0.5f;
	sonic_action[11].mtnmode = 9;

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

static void ReplaceSonicModels()
{
	SHADOW_OBJECT_000 = OpenModel("SHADOW_OBJECTS\\000.sa1mdl"); // Shadow
	SHADOW_OBJECT_022 = OpenModel("SHADOW_OBJECTS\\022.sa1mdl"); // Super Shadow
	SHADOW_OBJECT_044 = OpenModel("SHADOW_OBJECTS\\044.sa1mdl"); // Ball model
	SHADOW_OBJECT_047 = OpenModel("SHADOW_OBJECTS\\047.sa1mdl"); // Event head
	SHADOW_OBJECT_054 = OpenModel("SHADOW_OBJECTS\\054.sa1mdl"); // Light Dash Aura
	SHADOW_OBJECT_058 = OpenModel("SHADOW_OBJECTS\\058.sa1mdl"); // Shoe Upgrade
	SHADOW_OBJECT_060 = OpenModel("SHADOW_OBJECTS\\060.sa1mdl"); // Shoe Upgrade
	SHADOW_OBJECT_063 = OpenModel("SHADOW_OBJECTS\\063.sa1mdl"); // Wrist Upgrade
	SHADOW_OBJECT_064 = OpenModel("SHADOW_OBJECTS\\064.sa1mdl"); // Ring upgrade (for display)
	SHADOW_OBJECT_065 = OpenModel("SHADOW_OBJECTS\\065.sa1mdl"); // Shoe upgrade (for display)
	SHADOW_OBJECT_066 = OpenModel("SHADOW_OBJECTS\\066.sa1mdl"); // Curved model
	SHADOW_ACTION_142 = OpenModel("SHADOW_ACTIONS\\142.sa1mdl"); // Super Shadow ball model
	SHADOW_MODEL_009  = OpenModel("SHADOW_MODELS\\009.sa1mdl");  // Morph head
	
	SONIC_OBJECTS[0] = SHADOW_OBJECT_000->getmodel();
	SONIC_OBJECTS[1] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[2] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[3] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[6] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[7] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[8] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[9] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[10] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[11] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[12] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[13] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[14] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[17] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[18] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[19] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[22] = SHADOW_OBJECT_022->getmodel();
	SONIC_OBJECTS[23] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[24] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[25] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[26] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[27] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[28] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[29] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[30] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[31] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[32] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[33] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[34] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[35] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[36] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[37] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[38] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[39] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->sibling;
	SONIC_OBJECTS[40] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling;
	SONIC_OBJECTS[41] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[42] = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[44] = SHADOW_OBJECT_044->getmodel();
	SONIC_OBJECTS[45] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling;
	SONIC_OBJECTS[46] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling;
	SONIC_OBJECTS[47] = SHADOW_OBJECT_047->getmodel();
	SONIC_OBJECTS[48] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child;
	SONIC_OBJECTS[49] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling;
	SONIC_OBJECTS[50] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling;
	SONIC_OBJECTS[51] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->child->child->sibling;
	SONIC_OBJECTS[52] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->child->child->sibling;
	SONIC_OBJECTS[54] = SHADOW_OBJECT_054->getmodel();
	SONIC_OBJECTS[55] = SONIC_OBJECTS[54]->child->child->sibling->sibling->sibling->sibling->sibling;
	SONIC_OBJECTS[58] = SHADOW_OBJECT_058->getmodel();
	SONIC_OBJECTS[59] = SONIC_OBJECTS[58]->child;
	SONIC_OBJECTS[60] = SHADOW_OBJECT_060->getmodel();
	SONIC_OBJECTS[61] = SONIC_OBJECTS[60]->child;
	SONIC_OBJECTS[62] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child;
	SONIC_OBJECTS[63] = SHADOW_OBJECT_063->getmodel()->child;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];
	SONIC_OBJECTS[64] = SHADOW_OBJECT_064->getmodel();
	SONIC_OBJECTS[65] = SHADOW_OBJECT_065->getmodel();
	SONIC_OBJECTS[66] = SHADOW_OBJECT_066->getmodel();
	SONIC_OBJECTS[67] = SONIC_OBJECTS[44];
	
	SONIC_ACTIONS[0]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[1]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[2]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[3]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[4]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[5]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[6]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[7]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[8]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[9]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[10]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[11]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[12]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[13]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[14]->object = SONIC_OBJECTS[66];
	SONIC_ACTIONS[15]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[16]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[17]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[18]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[19]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[20]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[21]->object = SONIC_OBJECTS[44];
	SONIC_ACTIONS[22]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[23]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[27]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[28]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[29]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[30]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[31]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[32]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[33]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[34]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[35]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[36]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[37]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[38]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[39]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[40]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[41]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[42]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[43]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[44]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[45]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[46]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[47]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[48]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[49]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[50]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[51]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[52]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[53]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[54]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[55]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[56]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[57]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[58]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[59]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[60]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[61]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[62]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[63]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[64]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[65]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[66]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[67]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[68]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[69]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[70]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[71]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[72]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[87]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[88]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[89]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[90]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[91]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[92]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[93]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[94]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[95]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[96]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[97]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[98]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[99]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[100]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[101]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[102]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[103]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[104]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[105]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[106]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[107]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[108]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[109]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[113]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[114]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[115]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[116]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[117]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[118]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[119]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[120]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[121]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[122]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[123]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[124]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[125]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[126]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[127]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[128]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[129]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[130]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[131]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[132]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[133]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[134]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[135]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[136]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[137]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[138]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[139]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[140]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[141]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[142]->object = SHADOW_ACTION_142->getmodel();
	SONIC_ACTIONS[143]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[144]->object = SONIC_OBJECTS[22];
	SONIC_ACTIONS[145]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[146]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[147]->object = SONIC_OBJECTS[0];
	SONIC_ACTIONS[148]->object = SONIC_OBJECTS[0];

	SONIC_MODELS[0] = nullptr; // Base Shoe Toe (Left)
	SONIC_MODELS[1] = nullptr; // Base Shoe Toe (Right)
	SONIC_MODELS[2] = nullptr; // Stretched Toe 01 (Left)
	SONIC_MODELS[3] = nullptr; // Stretched Toe 02 (Left)
	SONIC_MODELS[4] = nullptr; // Stretched Toe 03 (Left)
	SONIC_MODELS[5] = nullptr; // Stretched Toe 01 (Right)
	SONIC_MODELS[6] = nullptr; // Stretched Toe 02 (Right)
	SONIC_MODELS[7] = nullptr; // Stretched Toe 03 (Right)
	SONIC_MODELS[8] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->basicdxmodel; // Normal head
	SONIC_MODELS[9] = SHADOW_MODEL_009->getmodel()->basicdxmodel; // Morph head
}

static void ReplaceSonicAnims()
{
	SHADOW_ACTION_005 = OpenAnim("SHADOW_ACTIONS\\005.saanim");  // Jog
	SHADOW_ACTION_006 = OpenAnim("SHADOW_ACTIONS\\006.saanim");  // Run
	SHADOW_ACTION_018 = OpenAnim("SHADOW_ACTIONS\\018.saanim");  // Run fast
	
	SONIC_ACTIONS[5]->motion  = SHADOW_ACTION_005->getmotion();
	SONIC_ACTIONS[6]->motion  = SHADOW_ACTION_006->getmotion();
	SONIC_ACTIONS[18]->motion = SHADOW_ACTION_018->getmotion();
}

static void ReplaceSonicShapeMotions()
{
	SHADOW_MOTION_000 = OpenAnim("SHADOW_MOTIONS\\000.saanim");  // Shape motions

	SONIC_MOTIONS[0] = SHADOW_MOTION_000->getmotion();
}

static void ReplaceSonicPointingFinger()
{
	ModelInfo* mdl = OpenModel("SHADOW_POINTINGHAND.sa1mdl");

	if (mdl)
	{
		SonicPointingHand_Object.model = mdl->getmodel()->model;
	}
}

void HookCHRMODELS()
{
	ReplaceSonicModels();
	ReplaceSonicShapeMotions();
	ReplaceSonicPointingFinger();

	// Replace welds
	InitSonicWeldInfo_h.Hook(InitSonicWeldInfo_r);
	WriteJump(InitNPCSonicWeldInfo, InitNPCSonicWeldInfo_r);

	if (config::bCustomAnims)
	{
		ReplaceSonicAnims();

		// Set new animation settings
		InitSonicAnimData_h.Hook(InitSonicAnimData_r);
	}
}
