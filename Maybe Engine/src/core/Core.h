#pragma once

#include "Log.h"

#define ASSERT(x, ...) { if(!(x)) { mb::Log::Error("Core Error - {}!", __VA_ARGS__); __debugbreak(); } }