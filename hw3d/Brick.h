#pragma once
#include "Rect.h"
#include "Color.h"
#include "Graphics.h"

class Ball;

class Brick
{
    public:

        Brick() = default;
        Brick( const Rect &rect, Color color );

        void Draw( Graphics &gfx ) const;

        Vector2 GetCenter() const;
        void    SetImmortal( bool isImmortal );
        bool    GetIsBroken() const;

        bool DoCollisionWithBall( Ball &ball );
        bool CheckBallCollision( const Ball &ball ) const; // TODO: useful

    private:

        bool  mIsImmortal = false;
        bool  mIsBroken   = false;
        Color mColor;
        Rect  mRect; // implicit position
};
