#pragma once

#include "..\platform\ComponentManager.h"
#include "..\maths\maths.h"

namespace mb { namespace physics {

	class CollisionDetection
	{
	public:
		static bool Intersect(unsigned int ID1, unsigned ID2);
		static bool Intersect(const maths::Vec2& size1, const maths::Vec2& position1, const maths::Vec2& size2, const maths::Vec2& position2);
	};

} }