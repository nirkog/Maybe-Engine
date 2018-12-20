#include "CollisionDetection.h"
#include "..\maths\maths.h"

namespace mb { namespace physics {

	bool CollisionDetection::Intersect(unsigned int ID1, unsigned ID2)
	{
		maths::Vec2 position1 = platform::ComponentManager::GetComponent<platform::TransformComponent>(ID1)->position;
		maths::Vec2 position2 = platform::ComponentManager::GetComponent<platform::TransformComponent>(ID2)->position;
		maths::Vec2 size1 = platform::ComponentManager::GetComponent<platform::RenderComponent>(ID1)->sprite.GetSize();
		maths::Vec2 size2 = platform::ComponentManager::GetComponent<platform::RenderComponent>(ID2)->sprite.GetSize();
		
		if (position1.x + size1.x / 2 > position2.x - size2.x / 2 && position1.x - size1.x / 2 < position2.x + size2.x / 2)
			if (position1.y + size1.y / 2 > position2.y - size2.y / 2 && position1.y - size1.y / 2 < position2.y + size2.y / 2)
				return true;

		return false;
	}

} }