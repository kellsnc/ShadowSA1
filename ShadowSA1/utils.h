#pragma once

#define CALL_ORIGINAL(name) ((decltype(name##_r)*)name##_t->Target())

ModelInfo* OpenModel(std::string path);
AnimationFile* OpenAnim(std::string path);