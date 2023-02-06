#include "Application.h"
#include "Color.h"
#include "Timer.h"
#include "Rect.h"
#include "Brick.h"
#include "Ball.h"

Application::Application(Window& wnd):
	mWindow(wnd)
{ }

int Application::Run() {

	while (mWindow.ProcessMessage())
	{
		DoFrame();

		//if (mWindow.kbd.KeyIsPressed(VK_SPACE)){
		//	MessageBox(nullptr, "Something Happened!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
		//	return 0;
		//}
	}
	return 0;
}

void Application::DoFrame()
{
	mWindow.gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	mWindow.gfx.EndFrame();
}

void Application::UpdateModel()
{
}

void Application::ComposeFrame()
{
	Brick brick1(Rect(40.0f, 100.0f, 40.0f, 60.0f), Colors::Yellow);
	brick1.Draw(mWindow.gfx);
	Ball ball(Vector2(40.0f, 80.0f), Vector2(40.0f, 80.0f));
	ball.Draw(mWindow.gfx);
}

void Application::TrippinBackground() {
	const float red = sin(mTimer.Peek()) / 2.0f + 0.5f;
	const float green = sin(mTimer.Peek()) / 2.0f + 0.5f;
	mWindow.gfx.ClearBuffer(red, green, 1.0f);
	//mWindow.gfx.DrawTriangleTest();
	//mWindow.gfx.EndFrame();
}
