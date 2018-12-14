#include "ComponentManager.h"

namespace mb { namespace platform {

	std::map<unsigned int, std::map<unsigned int, BaseComponent*>> ComponentManager::data;
	unsigned int ComponentManager::componentCount = 0;

} }