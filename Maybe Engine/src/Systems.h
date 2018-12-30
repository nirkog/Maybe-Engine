#pragma once

#include <chrono>
#include <thread>
#include <sstream>

#include "platform\System.h"
#include "graphics\window.h"
#include "input\input.h"
#include "maths\maths.h"

using namespace mb::platform;
using namespace mb::input;
using namespace mb::graphics;

class MovementSystem : public System 
{
public:
	MovementSystem(Window& window) 
	{
		m_ComponentIds.push_back(TransformComponent::ID);

		windowSize = window.GetSize();
		m_Window = &window;
	}

	~MovementSystem()
	{

	}

	void OnInitEntity(unsigned int entityID)
	{
		auto* transform = ComponentManager::GetComponent<TransformComponent>(entityID);

		if (EntityManager::GetTag(entityID) == "PADDLE1")
			paddle1ID = entityID;
		else if (EntityManager::GetTag(entityID) == "PADDLE2")
			paddle2ID = entityID;

		transform->accleration = {0, 0};
		transform->velocity = {0, 0};

		transforms.push_back(transform);
	}

	void OnUpdate(float deltaTime)
	{
		for (unsigned int i = 0; i < m_EntityCount; i++)
		{
			const unsigned int id = m_EntityIds[i];
			auto* transform = transforms[i];

			if (EntityManager::GetTag(id) == "BALL")
			{
				transform->rotationAngle += 125 * deltaTime;
				transform->scale.x = mb::maths::abs(mb::maths::sin(mb::utils::Time::GetElapsedTime())) + 1;
				transform->scale.y = mb::maths::abs(mb::maths::sin(mb::utils::Time::GetElapsedTime())) + 1;

				const Sprite2D sprite = ComponentManager::GetComponent<RenderComponent>(id)->sprite;
				const mb::maths::Vec2 size = sprite.GetSize();

				if (transform->position.y + size.y / 2 >= windowSize.y / 2)
				{
					transform->position.y = windowSize.y / 2 - size.y / 2;
					transform->velocity.y *= -1;
				}
				else if (transform->position.y - size.y / 2 <= -windowSize.y / 2)
				{
					transform->position.y = -windowSize.y / 2 + size.y / 2;
					transform->velocity.y *= -1;
				}
				else if (transform->position.x + size.x / 2 >= windowSize.x / 2 || transform->position.x - size.x / 2 <= -windowSize.x / 2)
				{
					if (transform->position.x > 0) ComponentManager::GetComponent<ScoreComponent>(paddle1ID)->score++;
					else ComponentManager::GetComponent<ScoreComponent>(paddle2ID)->score++;

					const unsigned int paddle1Score = ComponentManager::GetComponent<ScoreComponent>(paddle1ID)->score;
					const unsigned int paddle2Score = ComponentManager::GetComponent<ScoreComponent>(paddle2ID)->score;

					std::stringstream stream;
					stream << paddle1Score << " - " << paddle2Score;
					m_Window->SetTitle(stream.str().c_str());

					mb::utils::Log::Error("You suck! the score is {} - {}!", paddle1Score, paddle2Score);

					transform->position = mb::maths::Vec2(0, 0);
					std::this_thread::sleep_for(std::chrono::milliseconds(750));
				}
				else if (transform->velocity.x > 0)
				{
					if (mb::physics::CollisionDetection::Intersect(id, paddle2ID))
						transform->velocity.x *= -1;
				}
				else if (transform->velocity.x < 0)
				{
					if (mb::physics::CollisionDetection::Intersect(id, paddle1ID))
						transform->velocity.x *= -1;
				}
			}

			transform->position += transform->velocity * deltaTime;
			transform->velocity += transform->accleration * deltaTime;

			if (id == paddle1ID || id == paddle2ID)
			{
				const Sprite2D sprite = ComponentManager::GetComponent<RenderComponent>(id)->sprite;
				const mb::maths::Vec2 size = sprite.GetSize();

				if (transform->position.y + size.y / 2 > windowSize.y / 2)
				{
					transform->position.y = windowSize.y / 2 - size.y / 2;
				}
				else if (transform->position.y - size.y / 2 < -windowSize.y / 2)
				{
					transform->position.y = -windowSize.y / 2 + size.y / 2;
				}
			}
		}
	}
private:
	std::vector<TransformComponent*> transforms;
	mb::maths::Vec2 windowSize;
	mb::graphics::Window* m_Window;
	unsigned int paddle1ID, paddle2ID;
};

class InputSystem : public System
{
public:
	InputSystem()
		: speed(275)
	{
		m_ComponentIds.push_back(TransformComponent::ID);
		m_ComponentIds.push_back(InputComponent::ID);
	}

	~InputSystem()
	{

	}

	void OnInitEntity(unsigned int entityID)
	{
		auto* transform = ComponentManager::GetComponent<TransformComponent>(entityID);
		auto* input = ComponentManager::GetComponent<InputComponent>(entityID);

		transforms.push_back(transform);
		inputs.push_back(input);
	}

	void OnUpdate(float deltaTime)
	{
		for (unsigned int i = 0; i < m_EntityCount; i++)
		{
			auto* transform = transforms[i];
			auto* input = inputs[i];

			if (Input::IsKeyPressed((Key)input->upKey))
			{
				transform->velocity.y = speed;
			}
			else if (Input::IsKeyPressed((Key)input->downKey))
			{
				transform->velocity.y = -speed;
			}
			else
			{
				transform->velocity.y = 0;
			}
		}
	}
private:
	std::vector<TransformComponent*> transforms;
	std::vector<InputComponent*> inputs;

	float speed;
};