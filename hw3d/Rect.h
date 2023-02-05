#pragma once

#include "Vector2.h"

class Rect
{
public:
	Rect() = default;
	Rect(float left_in, float right_in, float top_in, float bottom_in);
	Rect(const Vector2& topLeft, const Vector2& bottomRight);
	Rect(const Vector2& topLeft, float width, float height);
	bool IsOverlappingWith(const Rect& other) const;
	bool IsContainedBy(const Rect& other) const;
	static Rect FromCenter(const Vector2& center, float halfWidth, float halfHeight);
	Rect GetExpanded(float offset) const;
	Vector2 GetCenter() const;
public:
	float left;
	float right;
	float top;
	float bottom;
};

