#pragma once

#include <vector>
#include <map>
#include <memory>

#include "Component.h"

namespace mb { namespace platform { 

	class ComponentManager
	{
	public:
		template<typename T>
		static T* AddComponent(const unsigned int entityID, std::vector<unsigned int> componentIds)
		{
			unsigned int id = T::ID;
			if (data.find(id) == data.end())
			{ 
				//std::cout << "New Map! (component id is " << id << ")" << std::endl;

				std::map<unsigned int, BaseComponent*> newComponentMap;
				T* comp = new T();

				std::pair<unsigned int, BaseComponent*> pair;
				pair.first = entityID;
				pair.second = comp;

				newComponentMap.insert(pair);
				data.insert({id, newComponentMap});

				std::pair<unsigned int, unsigned int> sizePair;
				sizePair.first = id;
				sizePair.second = sizeof(T);

				//std::cout << "Adding component with size " << sizePair.second << std::endl;

				componentSizes.insert(sizePair);

				componentCount++;

				SystemManager::AddEntity(componentIds, entityID);

				return comp;
			}
			else
			{
				//std::cout << "Existing Map! (component id is " << id << ")" << std::endl;

				std::map<unsigned int, BaseComponent*> &componentMap = data.find(id)->second;

				if (componentMap.find(entityID) != componentMap.end())
				{
					std::cout << "Warning: Trying to add an existing component to an entity! eid " << entityID << std::endl;
					return (T*) componentMap.find(entityID)->second;
				}

				T* comp = new T();

				std::pair<unsigned int, BaseComponent*> pair;
				pair.first = entityID;
				pair.second = comp;

				componentMap.insert(pair);

				SystemManager::AddEntity(componentIds, entityID);

				return comp;
			}
		}

		template<typename T>
		static void PrintComponentMap()
		{
			unsigned int id = T::ID;
			if (data.find(id) != data.end())
			{ 
				std::map<unsigned int, BaseComponent*> &componentMap = data.find(id)->second;

				for (auto& comp : componentMap)
				{
					std::cout << "Entity id " << comp.first << std::endl;
					if (comp.second == nullptr)
						std::cout << "Component is null!" << std::endl;
				}
			}
		}

		template<typename T>
		static T* GetComponent(unsigned int entityID)
		{
			unsigned int id = T::ID;
			if (data.find(id) != data.end())
			{
				std::map<unsigned int, BaseComponent*> &componentMap = data.find(id)->second;

				if (componentMap.find(entityID) != componentMap.end())
				{
					return (T*) componentMap.find(entityID)->second;
				}

				return nullptr;
			}

			return nullptr;
		}

		static void DestroyEntityData(unsigned int id);

		static void DuplicateEntity(unsigned int originalID, unsigned int duplicateID, std::vector<unsigned int> componentIds);

		static void Destroy()
		{
			for (std::pair<unsigned int, std::map<unsigned int, BaseComponent*>> compMap : data)
			{
				for (auto& comp : compMap.second)
				{
					delete comp.second;
				}
			}
		}
	private:
		static std::map<unsigned int, std::map<unsigned int, BaseComponent*>> data;
		static std::map<unsigned int, unsigned int> componentSizes;
		static unsigned int componentCount;
	};

} }