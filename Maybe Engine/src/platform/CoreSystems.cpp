#include "CoreSystems.h"

namespace mb { namespace platform { namespace coreSystems {

	void RenderingSystem::OnInitEntity(unsigned int entityID)
	{
		m_RenderComponents.push_back(ComponentManager::GetComponent<RenderComponent>(entityID));
		m_TransformComponents.push_back(ComponentManager::GetComponent<TransformComponent>(entityID));
	}

	void RenderingSystem::OnUpdate(float deltaTime)
	{
		renderer->Begin();
		for (unsigned int i = 0; i < m_EntityCount; i++)
		{
			if (m_RenderComponents[i]->animation.Enabled())
			{
				m_RenderComponents[i]->animation.Update();
				m_RenderComponents[i]->sprite.SetSpriteSheetPosition(m_RenderComponents[i]->animation.GetPosition().x, m_RenderComponents[i]->animation.GetPosition().y);
			}

			renderer->Submit(m_TransformComponents[i], m_RenderComponents[i]);
		}
		renderer->End();
	}

} } }