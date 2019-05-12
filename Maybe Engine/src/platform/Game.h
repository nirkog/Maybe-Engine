#pragma once

#include "..\graphics\graphics.h"
#include "..\utils\utils.h"
#include "..\platform\SystemManager.h"

namespace mb { namespace platform {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Run();
	protected:
		graphics::Window* m_Window;
	};

} }