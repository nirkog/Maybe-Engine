#pragma once

#include <vector>

#include "ComponentManager.h"

namespace mb { namespace platform {

	class Entity
	{
	public:
		Entity();
		~Entity();

		inline unsigned int GetID() const { return m_ID; }

		template<typename T>
		T* AddComponent()
		{
			m_ComponentIds.push_back(T::ID);
			return ComponentManager::AddComponent<T>(m_ID, m_ComponentIds);
		}

		template <typename T>
		T* GetComponent()
		{
			return ComponentManager::GetComponent<T>(m_ID);
		}
	public:
		static unsigned int lastID;
		static std::vector<unsigned int> freeIDs;
	private:
		unsigned int m_ID;
		std::vector<unsigned int> m_ComponentIds;
	};

}}