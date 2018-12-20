#include "SystemManager.h"

namespace mb { namespace platform {

	std::vector<System*> SystemManager::systems;

	void SystemManager::AddSystem(System* system)
	{
		systems.push_back(system);
	}


	void SystemManager::Update()
	{
		for (unsigned int i = 0; i < systems.size(); i++)
		{
			systems[i]->OnUpdate(utils::Time::GetDeltaTime());
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