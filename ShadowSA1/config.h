#pragma once

namespace config
{
	extern std::string modPath;

	extern bool bIcons;
	extern bool bAirEffects;
	extern bool bTornadoHack;
	extern bool bCustomAnims;

	void init(const char* path);
}