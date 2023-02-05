#pragma once
#include "Rect.h"
#include "Color.h"
#include "Graphics.h"

class Brick
{
public:
	Brick() = default;
	Brick(const Rect& rect, Color color);
	void Draw(Graphics& gfx) const;
	Vector2 GetCenter() const;
private:
	Rect mRect;
	Color mColor;
	bool mIsDestroyed = true;
};

