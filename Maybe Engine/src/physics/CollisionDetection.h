#pragma once

#include "..\platform\ComponentManager.h"

namespace mb { namespace physics {

	class CollisionDetection
	{
	public:
		static bool Intersect(unsigned int ID1, unsigned ID2);
	};

} }