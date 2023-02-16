#include "Brick.h"
#include "Ball.h"
#include <cmath>
#include <assert.h>

Brick::Brick( const Rect &rect, Color color )
    : mRect( rect )
    , mColor( color )
{

}

void Brick::Draw( Graphics &gfx ) const
{
    if ( !mIsBroken )
    {
        gfx.DrawRectangle( mRect, mColor );
    }
}

Vector2 Brick::GetCenter() const
{
    return mRect.GetCenter();
}

void Brick::SetImmortal( bool isImmortal )
{
    mIsImmortal = isImmortal;
}

bool Brick::GetIsBroken() const
{
    return mIsBroken;
}

bool Brick::CheckBallCollision( const Ball &ball ) const
{
    return !mIsBroken && mRect.IsOverlappingWith( ball.GetRect() );
}

bool Brick::DoCollisionWithBall( Ball &ball )
{
    if ( mIsBroken ) return false;
    if ( mRect.IsOverlappingWith( ball.GetRect() ) )
    {
        const Vector2 ballPos = ball.Pos();

        if ( std::signbit( ball.Dir().x ) == std::signbit( ( ballPos - GetCenter() ).x ) ) // from down
        {
            ball.BounceY();
        }
        else if ( ballPos.x >= mRect.left && ballPos.x <= mRect.right )                    // from up
        {
            ball.BounceY();
        }
        else
        {
            ball.BounceX();
        }

        if ( !mIsImmortal )
        {
            mLives--;
            mColor.SetG( mColor.GetG() - ( unsigned char ) 50 );

            if ( mLives <= 0 )
            {
                mIsBroken = true;
                return true; // a brick has died
            }
        }
    }

    return false;
}
