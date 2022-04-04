#pragma once

#define CALL_ORIGINAL(name) ((decltype(name##_r)*)name##_t->Target())
extern std::string ModPath;