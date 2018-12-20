#include "ComponentManager.h"
#include "SystemManager.h"

namespace mb { namespace platform {

	std::map<unsigned int, std::map<unsigned int, BaseComponent*>> ComponentManager::data;
	std::map<unsigned int, unsigned int> ComponentManager::componentSizes;
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

	void ComponentManager::DuplicateEntity(unsigned int originalID, unsigned int duplicateID, std::vector<unsigned int> componentIds)
	{
		DestroyEntityData(duplicateID);

		for (unsigned int i = 0; i < componentIds.size(); i++)
		{
			//std::cout << "Starting with component id " << componentIds[i] << " that has a size of " << componentSizes.find(componentIds[i])->second << std::endl;

			std::map<unsigned int, BaseComponent*> &componentMap = data.find(componentIds[i])->second;
			BaseComponent* comp = componentMap.find(originalID)->second;

			BaseComponent* newComp = (BaseComponent*) malloc(componentSizes.find(componentIds[i])->second);
			std::memcpy(newComp, comp, componentSizes.find(componentIds[i])->second);

			std::pair<unsigned int, BaseComponent*> pair;
			pair.first = duplicateID;
			pair.second = newComp;

			componentMap.insert(pair);
		}

		SystemManager::AddEntity(componentIds, duplicateID);
	}

} }