#include "Application.h"
#include "Color.h"
#include "Timer.h"
#include "Rect.h"
#include "Brick.h"
#include "Ball.h"

Application::Application( Window &wnd )
    : mWindow( wnd )
    , mBall( Vector2( Graphics::ScreenWidth / 2, Graphics::ScreenHeight * 6 / 8 ), Vector2( -10.f, -100.f ) )
    , mPaddle( Vector2( Graphics::ScreenWidth / 2, Graphics::ScreenHeight * 7 / 8 ), 80.0f, 10.0f )
{
    // mBall.SetPosition( Vector2 ( Graphics::ScreenWidth / 2, Graphics::ScreenHeight * 6 / 8) );
    SetBricksInGrid( mBricks );
    SetWalls( mWalls );
}

int Application::Run()
{
    while ( mWindow.ProcessMessage() )
    {
        if ( mBall.Pos().y > ballDeathHeightTresh )
        {
            MessageBox( nullptr, "GAME OVER", "Better luck next time!", MB_OK | MB_ICONEXCLAMATION );
            exit( EXIT_SUCCESS );
        }

        if ( numOfBricksLeft < 1 )
        {
            MessageBox( nullptr, "YOU WON", "You've been promoted to Arkanoid master.", MB_OK | MB_ICONEXCLAMATION );
            exit( EXIT_SUCCESS );
        }

        DoFrame();
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

    mPaddle.Update( mWindow.kbd, dt );

    mBall.Update( dt );

    mPaddle.DoBallCollision( mBall );

    for ( Brick &brick : mBricks )
    {
        if ( brick.DoCollisionWithBall( mBall ) )
            numOfBricksLeft--;
    }

    for ( Brick &wall : mWalls )
    {
        wall.DoCollisionWithBall( mBall );
    }
}

void Application::ComposeFrame()
{
    mBall.Draw( mWindow.gfx );

    mPaddle.Draw( mWindow.gfx );

    for ( const Brick &wall : mWalls )
    {
        wall.Draw( mWindow.gfx );
    }

    for ( const Brick &brick : mBricks )
    {
        brick.Draw( mWindow.gfx );
    }
}

void Application::TrippinBackground()
{
    const float red   = sin( mTimer.Peek() ) / 2.0f + 0.5f;
    const float green = sin( mTimer.Peek() ) / 2.0f + 0.5f;
    mWindow.gfx.ClearBuffer( red, green, 1.0f );
    // mWindow.gfx.DrawTriangleTest();
    // mWindow.gfx.EndFrame();
}

void Application::SetBallInPosition( Ball &ball )
{

}

void Application::SetWalls( std::vector< Brick > &walls )
{
    int sideWallWidth = 60.0f;
    int topWallHeight = 60.0f;

    // top wall

    Brick topWall( Rect( Vector2( 0, 0 ), Graphics::ScreenWidth, topWallHeight ), Colors::Blue );
    topWall.SetImmortal( true );
    mWalls.push_back( topWall );

    // temporary bottom wall

    // Brick bottomWall( Rect( Vector2( 0, Graphics::ScreenHeight - topWallHeight ), Graphics::ScreenWidth, topWallHeight ), Colors::Blue );
    // bottomWall.SetImmortal( true );
    // mWalls.push_back( bottomWall );

    // left wall

    Brick sideLeftWall( Rect( Vector2( 0, 0 ), sideWallWidth, Graphics::ScreenHeight ), Colors::Blue );
    sideLeftWall.SetImmortal( true );
    mWalls.push_back( sideLeftWall );

    // right wall

    Brick sideRightWall( Rect( Vector2( Graphics::ScreenWidth - sideWallWidth, 0 ), sideWallWidth, Graphics::ScreenHeight ), Colors::Blue );
    sideRightWall.SetImmortal( true );
    mWalls.push_back( sideRightWall );
}

void Application::SetBricksInGrid( std::vector< Brick > &bricks )
{
    const int numBricksPerRow = 5;
    const int numBricksPerCol = 3;

    numOfBricksLeft = 5 * 3;

    const int firstBrickRowScreenHeight = Graphics::ScreenHeight / 8;
    const int PaddleScreenHeight        = Graphics::ScreenHeight * 2 / 8;

    const float spaceBetwBricks = 5.0f;

    const float brickWidth  = ( Graphics::ScreenWidth / ( numBricksPerRow + 1 ) ) - ( spaceBetwBricks );
    const float brickHeight = 35.0f;

    float posScreenHeight = firstBrickRowScreenHeight;

    for ( int i = 0; i < numBricksPerCol; i++ )
    {
        for ( int j = 1; j < numBricksPerRow + 1; j++ )
        {
            float posScreenWidth = Graphics::ScreenHeight * j / ( numBricksPerRow + 1 );

            Brick b( Rect::FromCenter( Vector2( posScreenWidth, posScreenHeight ), brickWidth / 2, brickHeight / 2 ), Colors::Yellow );
            bricks.push_back( b );
        }

        posScreenHeight += brickHeight + spaceBetwBricks;
    }
}
