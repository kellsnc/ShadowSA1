#include "pch.h"
#include "config.h"

ModelInfo* OpenModel(std::string path)
{
	path = config::modPath + "\\models\\" + path;

	auto file = new ModelInfo(path.c_str());

	if (file->getformat() == ModelFormat_Invalid)
	{
		PrintDebug("[ShadowSA1] Failed to load model at %s", path.c_str());
		delete file;
		return nullptr;
	}
	else
	{
		return file;
	}
}

AnimationFile* OpenAnim(std::string path)
{
	path = config::modPath + "\\models\\" + path;

	auto file = new AnimationFile(path.c_str());

	if (file->getmotion() == nullptr)
	{
		PrintDebug("[ShadowSA1] Failed to load animation at %s", path.c_str());
		delete file;
		return nullptr;
	}
	else
	{
		return file;
	}
}
