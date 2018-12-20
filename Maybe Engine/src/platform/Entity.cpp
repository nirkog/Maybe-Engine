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

	Entity::Entity(const char* tag)
		: m_Tag(tag)
	{
		if (freeIDs.size() == 0)
		{
			m_ID = lastID;
			lastID++;
		}
		else
		{
			m_ID = freeIDs[0];
			freeIDs.erase(freeIDs.begin());
		}

		EntityManager::SetTag(m_ID, tag);
	}

	Entity::~Entity()
	{
		ComponentManager::DestroyEntityData(m_ID);
		freeIDs.push_back(m_ID);
	}

	void Entity::Duplicate(Entity* duplicate)
	{
		duplicate->ClearComponentIds();

		for (unsigned int i = 0; i < m_ComponentIds.size(); i++)
		{
			duplicate->AddComponentId(m_ComponentIds[i]);
		}

		ComponentManager::DuplicateEntity(m_ID, duplicate->GetID(), m_ComponentIds);
	}

} }