#include "pch.h"
#include "IniFile.hpp"

namespace config
{
	std::string modPath;

	bool bIcons         = true;
	bool bAirEffects    = true;
	bool bTornadoHack   = true;
	bool bCustomAnims   = true;

	void init(const char* path)
	{
		modPath = path;

		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		const IniGroup* group = config->getGroup("");

		if (group)
		{
			bIcons         = group->getBool("Icon", bIcons);
			bAirEffects    = group->getBool("Air", bAirEffects);
			bTornadoHack   = group->getBool("Tornado", bTornadoHack);
			bCustomAnims   = group->getBool("Anims", bCustomAnims);
		}
		
		delete config;
	}
}
