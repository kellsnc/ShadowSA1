#include "pch.h"

ModelInfo* OpenModel(std::string path)
{
	path = ModPath + "\\models\\" + path;

	ModelInfo* file = new ModelInfo(path.c_str());

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
	path = ModPath + "\\models\\" + path;

	AnimationFile* file = new AnimationFile(path.c_str());

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

void Utils_Init(const char* path)
{
	ModPath = path;
}