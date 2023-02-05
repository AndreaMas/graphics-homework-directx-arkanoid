#include "Rect.h"

Rect::Rect(float left_in, float right_in, float top_in, float bottom_in):
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rect::Rect(const Vector2& topLeft, const Vector2& bottomRight):
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rect::Rect(const Vector2& topLeft, float width, float height):
	Rect(topLeft, topLeft + Vector2(width, height))
{
}

bool Rect::IsOverlappingWith(const Rect& other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rect::IsContainedBy(const Rect& other) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

Rect Rect::FromCenter(const Vector2& center, float halfWidth, float halfHeight)
{
	const Vector2 half(halfWidth, halfHeight);
	return Rect(center - half, center + half);
}

Rect Rect::GetExpanded(float offset) const
{
	return Rect(left - offset, right + offset, top - offset, bottom + offset);
}

Vector2 Rect::GetCenter() const
{
	return Vector2((left + right) / 2.0f, (top + bottom) / 2.0f);
}

