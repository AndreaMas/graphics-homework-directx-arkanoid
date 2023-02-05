#pragma once

#include "Vector2.h"

class Rectangle
{
public:
	Rectangle() = default;
	Rectangle(float left_in, float right_in, float top_in, float bottom_in);
	Rectangle(const Vector2& topLeft, const Vector2& bottomRight);
	Rectangle(const Vector2& topLeft, float width, float height);
	bool IsOverlappingWith(const Rectangle& other) const;
	bool IsContainedBy(const Rectangle& other) const;
	static Rectangle FromCenter(const Vector2& center, float halfWidth, float halfHeight);
	Rectangle GetExpanded(float offset) const;
	Vector2 GetCenter() const;
public:
	float left;
	float right;
	float top;
	float bottom;
};

