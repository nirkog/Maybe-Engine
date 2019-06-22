#include "CoreSystems.h"

namespace mb { namespace platform { namespace coreSystems {

	void RenderingSystem::OnInitEntity(unsigned int ID)
	{
		AddComponent<TransformComponent>(ID);
		AddComponent<RenderComponent>(ID);
	}

	void RenderingSystem::OnUpdateEntity(float deltaTime, unsigned int ID, std::vector<void*> comps)
	{
		auto* transform = (TransformComponent*) comps[0];
		auto* render = (RenderComponent*) comps[1];

		if (render->animation.Enabled())
		{
			render->animation.Update();
			render->sprite.SetSpriteSheetPosition(render->animation.GetPosition().x, render->animation.GetPosition().y);
		}

		renderer->Submit(transform, render);
	}

	void RenderingSystem::OnUpdateStart(float deltaTime)
	{
		renderer->Begin();
	}

	void RenderingSystem::OnUpdateEnd(float deltaTime)
	{
		renderer->End();
	}
	 
} } }