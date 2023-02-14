#pragma once

#include "WinWrap.h"
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"
#include <vector>

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

class Application
{
    public:

        Application( Window &wnd );

        int  Run();
        void DoFrame();
        void UpdateModel();
        void ComposeFrame();

        void TrippinBackground();

        void SetWalls( std::vector< Brick > &walls );
        void SetBricksInGrid( std::vector< Brick > &bricks );
        void SetBallInPosition( Ball &ball );

    private:

        const float resetGameTime        = 1.0f;
        const float ballDeathHeightTresh = Graphics::ScreenHeight - 40.0f;
        int         numOfBricksLeft      = 1;

        Window &mWindow;
        Timer   mTimer;

        Ball                 mBall;
        Paddle               mPaddle;
        std::vector< Brick > mBricks;
        std::vector< Brick > mWalls;
};
