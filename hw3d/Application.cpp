#include "Application.h"
#include "Color.h"
#include "Timer.h"

Application::Application(Window& wnd):
	mWindow(wnd)
{ }

int Application::Run() {

	while (mWindow.ProcessMessage())
	{

		if (mWindow.kbd.KeyIsPressed(VK_SPACE))
		{
			MessageBox(nullptr, "Something Happened!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
			return 0;
		}

		// Draw
		DoFrame();
	}
	return 0;
}

void Application::DoFrame()
{
	const float red = sin(mTimer.Peek()) / 2.0f + 0.5f;
	const float green = sin(mTimer.Peek()) / 2.0f + 0.5f;
	mWindow.gfx.ClearBuffer(red, green, 1.0f);
	mWindow.gfx.DrawTriangleTest();
	mWindow.gfx.EndFrame();
}

void Application::GameLogic() 
{
	//mWindow.gfx.ClearBuffer(Colors::LightGray);
	//mWindow.gfx.DrawTriangleTest();
	//mWindow.gfx.EndFrame();

	/////////////////////////// FOR FUTURE
	
	//mWindow.gfx.BeginFrame();

	//float deltaTime = mTimer.deltaTime(); // time betw frames

	//while (deltaTime > 0.0f)
	//{
	//	const float dt = std::min(0.0025f, deltaTime); // ???
	//	UpdateModel(dt);
	//	deltaTime -= dt;
	//}

	//ComposeFrame();

	//mWindow.gfx.EndFrame();
}
