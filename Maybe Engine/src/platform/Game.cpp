#include "Game.h"

namespace mb { namespace platform {

	Game::Game()
	{
		utils::Init();
		InitAL();
	}

	Game::~Game()
	{
		SystemManager::Destroy();

		m_Window->Destroy();

		utils::Terminate();

		TerminateAL();
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

	void Game::InitAL()
	{
		m_AlDevice = alcOpenDevice(NULL);
		if (!m_AlDevice) std::cout << "NOT OK";
		m_AlContext = alcCreateContext(m_AlDevice, NULL);
		alcMakeContextCurrent(m_AlContext);
		if (!m_AlContext) std::cout << "NOT OK";
	}

	void Game::TerminateAL()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_AlContext);
		alcCloseDevice(m_AlDevice);
	}

} }