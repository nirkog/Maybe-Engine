#pragma once

#include <iostream>

namespace mb { namespace platform {

	static unsigned int lastID = 0;

	struct BaseComponent
	{
	};

	template<typename T>
	struct Component : public BaseComponent
	{
		static const unsigned int ID;
	};

	template<typename T>
	const unsigned int Component<T>::ID(lastID++);

	struct TransformComponent : public Component<TransformComponent>
	{
		unsigned int x = 0, y = 0, z = 0;
	};

	struct HealthComponent : public Component<HealthComponent>
	{
		float hp = 0;
	};

}}

