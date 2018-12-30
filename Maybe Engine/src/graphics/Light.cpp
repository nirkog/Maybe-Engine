#include "Light.h"

namespace mb { namespace graphics {

	Light::Light(const maths::Vec3& position, const maths::Vec3& color)
		: m_Position(position), m_Color(color)
	{
	}

	Light::~Light()
	{
	}

	void Light::Attach(const platform::Entity& entity)
	{
		attachmentTransform = entity.GetComponent<platform::TransformComponent>();
		m_Position = { attachmentTransform->position, m_Position.z };
	}

	void Light::Attach(const platform::Entity& entity, const float height)
	{
		attachmentTransform = entity.GetComponent<platform::TransformComponent>();
		m_Position = { attachmentTransform->position, height };
	}

	void Light::Update()
	{
		m_Position = { attachmentTransform->position, m_Position.z };
	}

}}
