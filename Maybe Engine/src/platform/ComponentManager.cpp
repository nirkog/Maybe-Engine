#include "ComponentManager.h"

namespace mb { namespace platform {

	std::map<unsigned int, std::map<unsigned int, BaseComponent*>> ComponentManager::data;
	unsigned int ComponentManager::componentCount = 0;

	void ComponentManager::DestroyEntityData(unsigned int id)
	{
		for (auto& pair : data)
		{
			//std::cout << "Erased " << pair.second.erase(pair.second.find(id)) << " entity " << id << " component" << std::endl;
			if (pair.second.find(id) != pair.second.end())
			{
				delete pair.second.at(id);
				pair.second.erase(pair.second.find(id));
			}
		}
	}
} }