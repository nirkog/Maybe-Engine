#pragma once

#include <iostream>

#include "../maths/vec3.h"
#include "../graphics/Sprite2D.h"

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
		maths::Vec2 position, scale, rotationAxis;
		maths::Vec2 velocity, accleration;
		float rotationAngle;
	};

	struct RenderComponent : public Component<RenderComponent>
	{
		graphics::Sprite2D sprite;
	};

}}

