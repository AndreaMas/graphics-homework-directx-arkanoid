#include "Rectangle.h"

Rectangle::Rectangle(float left_in, float right_in, float top_in, float bottom_in):
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rectangle::Rectangle(const Vector2& topLeft, const Vector2& bottomRight):
	Rectangle(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rectangle::Rectangle(const Vector2& topLeft, float width, float height):
	Rectangle(topLeft, topLeft + Vector2(width, height))
{
}

bool Rectangle::IsOverlappingWith(const Rectangle& other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rectangle::IsContainedBy(const Rectangle& other) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

Rectangle Rectangle::FromCenter(const Vector2& center, float halfWidth, float halfHeight)
{
	const Vector2 half(halfWidth, halfHeight);
	return Rectangle(center - half, center + half);
}

Rectangle Rectangle::GetExpanded(float offset) const
{
	return Rectangle(left - offset, right + offset, top - offset, bottom + offset);
}

Vector2 Rectangle::GetCenter() const
{
	return Vector2((left + right) / 2.0f, (top + bottom) / 2.0f);
}

