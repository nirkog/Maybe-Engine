#include "Entity.h"

namespace mb { namespace platform {

	unsigned int Entity::lastID = 0;
	std::vector<unsigned int> Entity::freeIDs;

	Entity::Entity()
	{
		if(freeIDs.size() == 0)
		{
			m_ID = lastID;
			lastID++;
		}
		else
		{
			m_ID = freeIDs[0];
			freeIDs.erase(freeIDs.begin());
		}
	}

	Entity::~Entity()
	{
		ComponentManager::DestroyEntityData(m_ID);
		freeIDs.push_back(m_ID);
	}

} }