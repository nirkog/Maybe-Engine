#pragma once

#include <map>

namespace mb { namespace platform {

	class EntityManager
	{
	public:
		static void SetTag(unsigned int ID, const char* tag);

		static const char* GetTag(unsigned int ID);
	private:
		static std::map<unsigned int, const char*> tags;
	};

} }