#include "Application.h"
#include "Color.h"
#include "Timer.h"
#include "Rect.h"
#include "Brick.h"
#include "Ball.h"

Application::Application(Window& wnd):
	mWindow(wnd),
	mBall(Vector2(Graphics::ScreenWidth / 2, Graphics::ScreenHeight * 6 / 8), Vector2(100.f,100.f))
{
	//mBall.SetPosition( Vector2 ( Graphics::ScreenWidth / 2, Graphics::ScreenHeight * 6 / 8) );

}

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
	const float dt = mTimer.Mark();
	mBall.Update(dt);
}

void Application::ComposeFrame()
{
	SetBricksInGrid(mBricks);
	// SetPaddleInPosition(mPaddle);

	mBall.Draw(mWindow.gfx);
	for(const Brick& brick : mBricks) {
		brick.Draw(mWindow.gfx);
	}
}

void Application::TrippinBackground() {
	const float red = sin(mTimer.Peek()) / 2.0f + 0.5f;
	const float green = sin(mTimer.Peek()) / 2.0f + 0.5f;
	mWindow.gfx.ClearBuffer(red, green, 1.0f);
	//mWindow.gfx.DrawTriangleTest();
	//mWindow.gfx.EndFrame();
}

void Application::SetBallInPosition(Ball& ball)
{

	
}

void Application::SetBricksInGrid(std::vector<Brick>& bricks)
{
	const int numBricksPerRow = 8;
	const int numBricksPerCol = 4;

	const int firstBrickRowScreenHeight = Graphics::ScreenHeight / 8;
	const int PaddleScreenHeight = Graphics::ScreenHeight * 2 / 8;

	const float spaceBetwBricks = 5.0f;

	const float brickWidth = (Graphics::ScreenWidth / (numBricksPerRow + 1)) - ( spaceBetwBricks );
	const float brickHeight = 35.0f;

	float posScreenHeight = firstBrickRowScreenHeight;

	for (int i = 0; i < numBricksPerCol; i++) {

		for (int j = 1; j < numBricksPerRow + 1; j++) {

			float posScreenWidth = Graphics::ScreenHeight * j / ( numBricksPerRow + 1 );

			Brick b(Rect::FromCenter(Vector2(posScreenWidth, posScreenHeight), brickWidth/2, brickHeight/2), Colors::Yellow);
			bricks.push_back(b);

			
		}

		posScreenHeight += brickHeight + spaceBetwBricks;
	}
}
