#include "Sandbox.h"

class InputSystem : public System
{
public:
	InputSystem(Vec2 windowSize)
		: speed(350)
	{
		m_ComponentIds.push_back(TransformComponent::ID);
		m_ComponentIds.push_back(RenderComponent::ID);

		this->windowSize = windowSize;
	}

	~InputSystem()
	{

	}

	void OnInitEntity(unsigned int ID)
	{
		transform.push_back(ComponentManager::GetComponent<TransformComponent>(ID));
		render.push_back(ComponentManager::GetComponent<RenderComponent>(ID));
	}

	void OnUpdate(float deltaTime)
	{
		for (unsigned int i = 0; i < m_EntityCount; i++)
		{
			if (transform[i]->position.x >= this->windowSize.x * 1.1f / 2)
				transform[i]->position.x = -this->windowSize.x * 1.1f / 2;
			else if (transform[i]->position.x <= -this->windowSize.x * 1.1f / 2)
				transform[i]->position.x = this->windowSize.x * 1.1f / 2;
			else if (transform[i]->position.y >= this->windowSize.y * 1.1f / 2)
				transform[i]->position.y = -this->windowSize.y * 1.1f / 2;
			else if (transform[i]->position.y <= -this->windowSize.y * 1.1f / 2)
				transform[i]->position.y = this->windowSize.y * 1.1f / 2;

			if (Input::IsKeyDown(Key::D_KEY))
			{
				transform[i]->velocity = { speed, 0 };
				render[i]->animation.SetStartingPosition(0, 2);
				render[i]->animation.SetEndingPosition(5, 2);
			}
			else if (Input::IsKeyDown(Key::A_KEY))
			{
				transform[i]->velocity = { -speed, 0 };
				render[i]->animation.SetStartingPosition(0, 0);
				render[i]->animation.SetEndingPosition(5, 0);
			}
			else if (Input::IsKeyDown(Key::W_KEY))
			{
				transform[i]->velocity = { 0, speed };
				render[i]->animation.SetStartingPosition(0, 1);
				render[i]->animation.SetEndingPosition(5, 1);
			}
			else if (Input::IsKeyDown(Key::S_KEY))
			{
				transform[i]->velocity = { 0, -speed };
				render[i]->animation.SetStartingPosition(0, 3);
				render[i]->animation.SetEndingPosition(5, 3);
			}

			transform[i]->position += transform[i]->velocity * deltaTime;
		}
	}
private:
	std::vector<TransformComponent*> transform;
	std::vector<RenderComponent*> render;

	Vec2 windowSize;
	float speed;
};

Sandbox::Sandbox()
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor(Color::MAGENTA);
	m_Window->SetVsync(false);

	Time::EnableFpsLog();

	LogOpenGLDetails();

	SystemManager::AddSystem(new coreSystems::RenderingSystem(m_Window->GetSize()));
	SystemManager::AddSystem(new InputSystem(m_Window->GetSize()));

	rm.AddTexture("./res/trump_run.png", 0);

	alien.AddComponent<RenderComponent>();
	alien.GetComponent<RenderComponent>()->sprite = Sprite2D({ 100, 100 });
	alien.GetComponent<RenderComponent>()->sprite.SetTexture(rm.GetTexture(0));
	alien.GetComponent<RenderComponent>()->sprite.EnableSpriteSheet();
	alien.GetComponent<RenderComponent>()->sprite.SetSpriteSheet({ 6, 4 });
	alien.GetComponent<RenderComponent>()->animation.Enable();
	alien.GetComponent<RenderComponent>()->animation.SetFPS(30);
	alien.GetComponent<RenderComponent>()->animation.SetSpriteSheet(alien.GetComponent<RenderComponent>()->sprite.GetSpriteSheet());
	alien.AddComponent<TransformComponent>();
}

Sandbox::~Sandbox()
{
}