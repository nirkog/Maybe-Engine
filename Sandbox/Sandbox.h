#pragma once

#include "platform/platform.h"
#include "audio/audio.h"

using namespace mb::graphics;
using namespace mb::utils;
using namespace mb::platform;
using namespace mb::maths;
using namespace mb::input;
using namespace mb::audio;

class Sandbox : public Game
{
public:
	Sandbox();
	~Sandbox();
private:
	ResourceManager rm;
};