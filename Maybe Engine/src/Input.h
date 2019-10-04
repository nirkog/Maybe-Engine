#pragma once

#include "events/KeyEvents.h"
#include "events/MouseEvents.h"
#include "core/math/vec2.h"
#include "Application.h"

namespace mb {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static Vec2 GetMousePosition();
		static bool IsMouseButtonPressed(MouseButton button);
	};
}