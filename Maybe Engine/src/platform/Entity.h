#pragma once

#include <vector>
#include <memory>

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
			return ComponentManager::AddComponent<T>(m_ID);
		}

		template <typename T>
		T* GetComponent()
		{
			return ComponentManager::GetComponent<T>(m_ID);
		}
	public:
		static unsigned int lastID;
	private:
		unsigned int m_ID;
	};

}}