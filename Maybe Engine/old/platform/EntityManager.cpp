#include "EntityManager.h"

namespace mb { namespace platform {

	std::map<unsigned int, const char*> EntityManager::tags;

	void EntityManager::SetTag(unsigned int ID, const char* tag)
	{
		std::pair<unsigned int, const char*> pair;
		pair.first = ID;
		pair.second = tag;

		tags.insert(pair);
	}

	const char* EntityManager::GetTag(unsigned int ID)
	{
		auto tag = tags.find(ID);

		if (tag == tags.end())
			return "";
		return tag->second;
	}

} }