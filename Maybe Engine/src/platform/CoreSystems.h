#pragma once

#include "..\graphics\BatchRenderer.h"
#include "System.h"

namespace mb { namespace platform { namespace coreSystems {
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(const maths::Vec2& windowSize)
		{
			AddComponentType<TransformComponent>();
			AddComponentType<RenderComponent>();

			renderer = new graphics::BatchRenderer(windowSize);
		}

		~RenderingSystem()
		{
			delete renderer;
		}

		void OnInitEntity(unsigned int ID);
		void OnUpdateEntity(float deltaTime, unsigned int ID, std::vector<void*> comps);
		void OnUpdateStart(float deltaTime);
		void OnUpdateEnd(float deltaTime);
	private:
		graphics::BatchRenderer* renderer;
	};
} } }