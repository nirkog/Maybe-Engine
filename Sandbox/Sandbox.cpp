#include "Sandbox.h"

#include <fstream>

Sandbox::Sandbox()
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor(Color::GRAY);
	m_Window->SetVsync(false);

	Time::DisableFpsLog();
}

Sandbox::~Sandbox()
{
	Log::Warn("Destroying sandbox!");
}