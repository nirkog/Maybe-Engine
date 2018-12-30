#pragma once

#include <vector>

#include "..\utils\Log.h"
#include "ComponentManager.h"
#include "EntityManager.h"

namespace mb { namespace platform {

	class Entity
	{
	public:
		Entity();
		Entity(const char* tag);
		~Entity();

		inline unsigned int GetID() const { return m_ID; }

		template<typename T>
		T* AddComponent()
		{
			m_ComponentIds.push_back(T::ID);
			return ComponentManager::AddComponent<T>(m_ID, m_ComponentIds);
		}

		template <typename T>
		T* GetComponent() const
		{
			return ComponentManager::GetComponent<T>(m_ID);
		}

		void ClearComponentIds() { m_ComponentIds.clear(); };
		void AddComponentId(unsigned int id) { m_ComponentIds.push_back(id); }

		void Duplicate(Entity* duplicate);

		void SetTag(const char* tag)
		{
			EntityManager::SetTag(m_ID, tag);
			m_Tag = tag;
		}
	public:
		static unsigned int lastID;
		static std::vector<unsigned int> freeIDs;
	private:
		unsigned int m_ID;
		std::vector<unsigned int> m_ComponentIds;
		const char* m_Tag;
	};

}}