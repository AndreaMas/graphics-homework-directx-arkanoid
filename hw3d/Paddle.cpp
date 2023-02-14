#include <cmath>
#include "Paddle.h"

Paddle::Paddle( const Vector2 &pos_in, float halfWidth_in, float halfHeight_in )
    : mPos( pos_in )
    , halfWidth( halfWidth_in )
    , halfHeight( halfHeight_in )
    , exitXFactor( maximumExitRatio / halfWidth )
    , fixedZoneHalfWidth( halfWidth * fixedZoneWidthRatio )
    , fixedZoneExitX( fixedZoneHalfWidth * exitXFactor )
{

}

void Paddle::Draw( Graphics &gfx ) const
{
    Rect rect = GetRect();
    gfx.DrawRectangle( rect, mColor );
}

bool Paddle::DoBallCollision( Ball &ball )
{
    if ( ball.Pos().y > Graphics::ScreenHeight / 2 )
    {
        const Rect rect = GetRect();

        if ( rect.IsOverlappingWith( ball.GetRect() ) )
        {
            const Vector2 ballPos = ball.Pos();

            if ( std::signbit( ball.Vel().x ) == std::signbit( ( ballPos - mPos ).x )
                 || ( ballPos.x >= rect.left && ballPos.x <= rect.right ) )
            {
                Vector2     dir;
                const float xDifference = ballPos.x - mPos.x;

                if ( std::abs( xDifference ) < fixedZoneHalfWidth )
                {
                    if ( xDifference < 0.0f )
                    {
                        dir = Vector2( -fixedZoneExitX, -1.0f );
                    }
                    else
                    {
                        dir = Vector2( fixedZoneExitX, -1.0f );
                    }
                }
                else
                {
                    dir = Vector2( xDifference * exitXFactor, -1.0f );
                }

                dir.Normalize();
                ball.SetDirection( dir );
            }
            else
            {
                ball.BounceX();
            }

            return true;
        }
    }

    return false;
}

void Paddle::Update( const Keyboard &kbd, float dt )
{
    if ( kbd.KeyIsPressed( VK_LEFT ) )
    {
        if ( mPos.x < halfWidth + mPaddleHorizontalTreshold )
            return;

        mPos.x -= mSpeed * dt;
    }

    if ( kbd.KeyIsPressed( VK_RIGHT ) )
    {
        if ( mPos.x > Graphics::ScreenWidth - halfWidth - mPaddleHorizontalTreshold )
            return;

        mPos.x += mSpeed * dt;
    }
}

Rect Paddle::GetRect() const
{
    return Rect::FromCenter( mPos, halfWidth, halfHeight );
}
