#include "SystemManager.h"

namespace mb { namespace platform {

	std::vector<System*> SystemManager::systems;

	void SystemManager::AddSystem(System* system)
	{
		systems.push_back(system);
	}


	void SystemManager::Update()
	{
		float deltaTime = utils::Time::GetDeltaTime();
		for (unsigned int i = 0; i < systems.size(); i++)
		{
			systems[i]->OnUpdateStart(deltaTime);

			for(unsigned int j = 0; j < systems[i]->GetEntityCount(); j++)
				systems[i]->OnUpdateEntity(deltaTime, systems[i]->GetEntityIdAt(j), systems[i]->GetComponentsAtIndex(j));

			systems[i]->OnUpdateEnd(deltaTime);
		}
	}

	void SystemManager::Destroy()
	{
		for (unsigned int i = 0; i < systems.size(); i++)
		{
			delete systems[i];
		}
	}

	void SystemManager::AddEntity(std::vector<unsigned int> ids, unsigned int entityID)
	{
		for (unsigned int i = 0; i < systems.size(); i++)
		{
			systems[i]->Add(ids, entityID);
		}
	}

} }