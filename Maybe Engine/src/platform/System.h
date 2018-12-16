#pragma once

#include <iostream>

#include "ComponentManager.h"
#include "..\utils\Time.h"

namespace mb { namespace platform {

	class System
	{
	public:
		virtual ~System() 
		{
			std::cout << "Destorying 11111";
			if (m_ComponentIds != nullptr) delete m_ComponentIds;
		}

		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;

		virtual void AddEntity(unsigned int entityID) = 0;

		void Add(std::vector<unsigned int> ids, unsigned int entityID)
		{
			for (unsigned int i = 0; i < entityIds.size(); i++)
				if (entityID = entityIds[i]) return;

			unsigned int size = sizeof(m_ComponentIds) / sizeof(m_ComponentIds);
			if (ids.size() <= size)
			{
				for (unsigned int i = 0; i < ids.size(); i++)
				{
					bool found = true;
					for (unsigned int j = 0; j < size; j++)
					{
						if (m_ComponentIds[j] == ids[i]) break;
						else if (j == size - 1) found = false;
					}

					if (!found) return;
				}

				AddEntity(entityID);
			}
		}
	protected:
		unsigned int* m_ComponentIds = nullptr;
	private:
		std::vector<unsigned int> entityIds;
	};

	class MovementSystem : public System
	{
	public:
		MovementSystem()
		{
			m_ComponentIds = new unsigned int[1];
			m_ComponentIds[0] = TransformComponent::ID;
		}

		~MovementSystem() override
		{

		}

		void OnInit() override
		{
			gravity = -250;

			for (auto* transform : m_Transform)
			{
				transform->velocity = { 0, 0 };
				transform->accleration = { 0, gravity };
			}
		}

		void OnUpdate() override
		{
			for (auto* transform : m_Transform)
			{
				transform->position += transform->velocity * utils::Time::GetDeltaTime();
				transform->velocity += transform->accleration * utils::Time::GetDeltaTime();

				if (transform->position.y <= -350)
				{
					transform->position.y = -350;
					transform->velocity = { 0, 0 };
				}
			}
		}

		void AddEntity(unsigned int entityID)
		{
			m_Transform.push_back(ComponentManager::GetComponent<TransformComponent>(entityID));
		}
	private:
		std::vector<TransformComponent*> m_Transform;
		float gravity;
	};
}}