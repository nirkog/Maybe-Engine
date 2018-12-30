#pragma once

#include "..\graphics\BatchRenderer.h"
#include "System.h"

namespace mb { namespace platform { namespace coreSystems {
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(const mb::graphics::Window& window)
		{
			m_ComponentIds.push_back(RenderComponent::ID);
			m_ComponentIds.push_back(TransformComponent::ID);

			renderer = new graphics::BatchRenderer(window);
		}

		~RenderingSystem()
		{
			delete renderer;
		}

		void OnInitEntity(unsigned int entityID);
		void OnUpdate(float deltaTime);
	private:
		std::vector<RenderComponent*> m_RenderComponents;
		std::vector<TransformComponent*> m_TransformComponents;
		graphics::BatchRenderer* renderer;
	};
} } }