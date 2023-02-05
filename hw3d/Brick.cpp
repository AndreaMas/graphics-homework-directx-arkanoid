#include "Brick.h"
#include <cmath>
#include <assert.h>

Brick::Brick(const Rect& rect, Color color):
	mRect(rect),
	mColor(color),
	mIsDestroyed(false)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!mIsDestroyed)
	{
		gfx.DrawRectangle(mRect, mColor);
	}
}

Vector2 Brick::GetCenter() const
{
	return mRect.GetCenter();
}
