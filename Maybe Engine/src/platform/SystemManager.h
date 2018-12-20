#pragma once

#include <vector>

#include "System.h"

namespace mb { namespace platform {

	class SystemManager
	{
	public:
		static void AddSystem(System* system);
		static void AddEntity(std::vector<unsigned int> ids, unsigned int entityID);
		static void Update();
		static void Destroy();
	private:
		static std::vector<System*> systems;
	};

} }