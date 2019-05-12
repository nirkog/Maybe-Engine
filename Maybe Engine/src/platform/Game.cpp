#include "Game.h"

namespace mb { namespace platform {

	Game::Game()
	{
		utils::Init();
	}

	Game::~Game()
	{
		SystemManager::Destroy();

		m_Window->Destroy();
	}

	void Game::Run()
	{
		while (m_Window->Open())
		{
			utils::Update(m_Window);
			m_Window->Clear();

			SystemManager::Update();

			m_Window->Update();
		}
	}

} }