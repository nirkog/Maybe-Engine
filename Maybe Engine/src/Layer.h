#pragma once

#include "events/Event.h"

namespace mb
{
	class Layer
	{
	public:
		Layer() {}
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnEvent(Event& e) = 0;
	};
}