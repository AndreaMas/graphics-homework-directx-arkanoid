#include "Ball.h"
#include "Graphics.h"
#include "Vector2.h"
#include "Rect.h"

Ball::Ball(const Vector2& pos, const Vector2& dir):
	mPos(pos),
	mDir(dir.GetNormalized()),
	mColor(255,255,255)
{
}

void Ball::Draw(Graphics& gfx) const
{
	gfx.DrawCircle(
		mPos.x,
		mPos.y,
		mRadius,
		mColor
		);
}

void Ball::Update(float dt)
{
	mPos += mDir * mSpeed * dt;
}

void Ball::BounceX()
{
	mDir.x = -mDir.x;
}

void Ball::BounceY()
{
	mDir.y = -mDir.y;
}

void Ball::DoWallCollision(const Rect& walls)
{
	const Rect rect = GetRect();

	if (rect.left < walls.left)
	{
		mPos.x += walls.left - rect.left;
		BounceX();
	}
	else if (rect.right > walls.right)
	{
		mPos.x -= rect.right - walls.right;
		BounceX();
	}

	if (rect.top < walls.top)
	{
		mPos.y += walls.top - rect.top;
		BounceY();
	}
	else if (rect.bottom > walls.bottom)
	{
		mPos.y -= rect.bottom - walls.bottom;
		BounceY();
	}
}

Rect Ball::GetRect() const
{
	return Rect::FromCenter(mPos, mRadius, mRadius);
}

Vector2 Ball::Dir() const
{
	return mDir;
}

Vector2 Ball::Pos() const
{
	return mPos;
}

Vector2 Ball::Vel() const
{
	return mDir * mSpeed;
}

float Ball::Radius() const
{
	return mRadius;
}

void Ball::SetPosition(const Vector2& pos)
{
	mPos = pos;
}

void Ball::SetDirection(const Vector2& dir)
{
	mDir = dir;
}

void Ball::SetSpeed(const float speed)
{
	mSpeed = speed;
}


