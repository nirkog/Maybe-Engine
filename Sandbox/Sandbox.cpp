#include "Sandbox.h"

class InputSystem : public System
{
public:
	InputSystem(Vec2 windowSize)
		: speed(350)
	{
		AddComponentType<TransformComponent>();
		AddComponentType<RenderComponent>();

		this->windowSize = windowSize;
	}

	~InputSystem()
	{

	}

	void OnInitEntity(unsigned int ID)
	{
		AddComponent<TransformComponent>(ID);
		AddComponent<RenderComponent>(ID);
	}

	void OnUpdateEntity(float deltaTime, unsigned int ID, std::vector<void*> comps)
	{
		auto* transform = (TransformComponent*) comps[0];
		auto* render = (RenderComponent*) comps[1];

		if (transform->position.x >= this->windowSize.x * 1.1f / 2)
			transform->position.x = -this->windowSize.x * 1.1f / 2;
		else if (transform->position.x <= -this->windowSize.x * 1.1f / 2)
			transform->position.x = this->windowSize.x * 1.1f / 2;
		else if (transform->position.y >= this->windowSize.y * 1.1f / 2)
			transform->position.y = -this->windowSize.y * 1.1f / 2;
		else if (transform->position.y <= -this->windowSize.y * 1.1f / 2)
			transform->position.y = this->windowSize.y * 1.1f / 2;

		if (Input::IsKeyDown(Key::D_KEY))
		{
			transform->velocity = { speed, 0 };
			render->animation.SetStartingPosition(0, 2);
			render->animation.SetEndingPosition(5, 2);
		}
		else if (Input::IsKeyDown(Key::A_KEY))
		{
			transform->velocity = { -speed, 0 };
			render->animation.SetStartingPosition(0, 0);
			render->animation.SetEndingPosition(5, 0);
		}
		else if (Input::IsKeyDown(Key::W_KEY))
		{
			transform->velocity = { 0, speed };
			render->animation.SetStartingPosition(0, 1);
			render->animation.SetEndingPosition(5, 1);
		}
		else if (Input::IsKeyDown(Key::S_KEY))
		{
			transform->velocity = { 0, -speed };
			render->animation.SetStartingPosition(0, 3);
			render->animation.SetEndingPosition(5, 3);
		}

		transform->position += transform->velocity * deltaTime;
	}
private:
	Vec2 windowSize;
	float speed;
};

Sandbox::Sandbox()
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor(Color::MAGENTA);
	m_Window->SetVsync(false);

	Time::DisableFpsLog();

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
	alien.GetComponent<RenderComponent>()->animation.SetFPS(15);
	alien.GetComponent<RenderComponent>()->animation.SetSpriteSheet(alien.GetComponent<RenderComponent>()->sprite.GetSpriteSheet());
	alien.AddComponent<TransformComponent>();

}

Sandbox::~Sandbox()
{
}