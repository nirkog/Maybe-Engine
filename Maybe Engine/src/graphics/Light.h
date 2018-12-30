#pragma once

#include "..\maths\maths.h"
#include "..\platform\platform.h"

namespace mb { namespace graphics {

	class Light
	{
	public:
		Light() {}
		Light(const maths::Vec3& position, const maths::Vec3& color);
		~Light();

		const maths::Vec3& GetPosition() const { return m_Position; };
		const maths::Vec3& GetColor() const { return m_Color; };

		void SetPosition(const maths::Vec3& position) { m_Position = position; }
		void SetColor(const maths::Vec3& color) { m_Color = color; }

		void Attach(const platform::Entity& entity);
		void Attach(const platform::Entity& entity, const float height);

		void Update();
	private:
		maths::Vec3 m_Position;
		maths::Vec3 m_Color;
		platform::TransformComponent* attachmentTransform;
	};

}}

