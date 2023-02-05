#pragma once

#include "WinWrap.h"
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"

class Application 
{
public:

	Application(Window& wnd);

	int Run();
	void GameLogic();
	void DoFrame();

private:

	Window& mWindow;
	Timer mTimer;
};
