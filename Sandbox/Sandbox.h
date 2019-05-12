#pragma once

#include "platform/platform.h"

#include "Systems.h"

using namespace mb::graphics;
using namespace mb::utils;
using namespace mb::platform;
using namespace mb::maths;
using namespace mb::input;

class Sandbox : public Game
{
public:
	Sandbox();
	~Sandbox();
private:
	Entity paddle1, paddle2, ball;
	ResourceManager rm;
};