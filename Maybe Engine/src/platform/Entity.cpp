#include "Entity.h"

namespace mb { namespace platform {

	unsigned int Entity::lastID = 0;

	Entity::Entity()
	{
		m_ID = lastID;
		lastID++;
	}

	Entity::~Entity()
	{
	}

} }