#pragma once

#include <map>

#include "ComponentManager.h"
#include "..\utils\Time.h"

namespace mb { namespace platform {

	struct ComponentsStorage
	{
		std::vector<unsigned int> m_ComponentIds;
		std::vector<std::pair<unsigned int, std::pair<std::vector<unsigned int>, std::vector<void*>>>> m_Components;

		template<typename T>
		void AddType()
		{
			m_ComponentIds.push_back(T::ID);
		}

		template<typename T>
		void AddComponent(T* component, unsigned int ID)
		{
			for (unsigned int i = 0; i < m_Components.size(); i++)
			{
				if (m_Components[i].first == ID)
				{
					m_Components[i].second.first.push_back(T::ID);
					m_Components[i].second.second.push_back((void*) component);

					return;
				}
			}

			std::vector<unsigned int> ids;
			ids.push_back(T::ID);

			std::vector<void*> comps;
			comps.push_back((void*) component);

			m_Components.push_back({ ID, { ids, comps } });
		}

		template<typename T>
		T* GetComponent(unsigned int ID)
		{
			for (unsigned int i = 0; i < m_Components.size(); i++)
			{
				if (m_Components[i].first == ID)
				{
					for (unsigned int j = 0; j < m_Components[i].second.first.size(); j++)
					{
						if (m_Components[i].second.first[j] == T::ID)
							return (T*) m_Components[i].second.second[j];
					}
				}
			}

			utils::Log::Warn("BAD ID");

			return nullptr;
		}

		std::vector<unsigned int> GetComponentIds()
		{
			return m_ComponentIds;
		}

		std::vector<void*> GetComponentsAtIndex(unsigned int i) const
		{
			return m_Components[i].second.second;
		}
	};

	class System
	{
	public:
		virtual ~System() {}

		virtual void OnInitEntity(unsigned int entityID) = 0;
		virtual void OnUpdateEntity(float deltaTime, unsigned int entityID, std::vector<void*> comps) = 0;
		virtual void OnUpdateStart(float deltaTime) {}
		virtual void OnUpdateEnd(float deltaTime) {}

		void Add(std::vector<unsigned int> ids, unsigned int entityID);

		unsigned int GetEntityCount() const { return m_EntityIds.size(); }
		unsigned int GetEntityIdAt(unsigned int i) const { return m_EntityIds[i]; }

		std::vector<void*> GetComponentsAtIndex(unsigned int i) const { return m_Components.GetComponentsAtIndex(i); }
	protected:
		template<typename T>
		void AddComponentType()
		{
			m_Components.AddType<T>();
		}

		template<typename T>
		void AddComponent(unsigned int ID)
		{
			m_Components.AddComponent<T>(ComponentManager::GetComponent<T>(ID), ID);
		}

		template<typename T>
		T* GetComponent(unsigned int ID)
		{
			return m_Components.GetComponent<T>(ID);
		}
	private:
		std::vector<unsigned int> m_EntityIds;
		ComponentsStorage m_Components;
	};
}}