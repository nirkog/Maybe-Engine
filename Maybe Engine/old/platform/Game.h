#pragma once

#include "..\graphics\graphics.h"
#include "..\utils\utils.h"
#include "..\platform\SystemManager.h"
#include "..\audio\AL.h"

namespace mb { namespace platform {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void InitAL();
		void TerminateAL();

		void Run();
	protected:
		graphics::Window* m_Window;

		ALCdevice* m_AlDevice;
		ALCcontext* m_AlContext;
	};

} }