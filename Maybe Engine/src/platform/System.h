#pragma once

#include <iostream>

#include "ComponentManager.h"
#include "..\utils\Time.h"

namespace mb { namespace platform {

	class System
	{
	public:
		virtual ~System() {}

		virtual void OnInitEntity(unsigned int entityID) = 0;
		virtual void OnUpdate(float deltaTime) = 0;

		void Add(std::vector<unsigned int> ids, unsigned int entityID);
	protected:
		std::vector<unsigned int> m_ComponentIds;
		unsigned int m_EntityCount = 0;
		std::vector<unsigned int> m_EntityIds;
	};
}}