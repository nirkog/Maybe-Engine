#pragma once

#include <iostream>

#include "../maths/vec3.h"
#include "../graphics/Sprite2D.h"
#include "../input/input.h"

namespace mb { namespace platform {

	struct BaseComponent
	{
		static unsigned int lastID;
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
		maths::Vec2 position = maths::Vec2(0, 0), scale = maths::Vec2(1, 1);
		maths::Vec3 rotationAxis = maths::Vec3(0, 0, 1);
		maths::Vec2 velocity = maths::Vec2(0, 0), accleration = maths::Vec2(0, 0);
		float rotationAngle = 0;
	};

	struct RenderComponent : public Component<RenderComponent>
	{
		graphics::Sprite2D sprite;
	};

	struct InputComponent : public Component<InputComponent>
	{
		unsigned int upKey, downKey;
	};

	struct ScoreComponent : public Component<ScoreComponent>
	{
		unsigned int score;
	};

}}

