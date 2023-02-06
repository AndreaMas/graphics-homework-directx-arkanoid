#pragma once

#include "Vector2.h"
#include "Rect.h"
#include "Color.h"

class Graphics;

class Ball
{
	public:

		enum class CollisionType {

		};

	public:

		Ball() = default;
		Ball(const Vector2& pos, const Vector2& dir);

		Vector2 Dir() const; // Getters
		Vector2 Pos() const;
		Vector2 Vel() const;
		float Radius() const;

		void SetPosition(const Vector2& pos); // Setters
		void SetDirection(const Vector2& dir);
		void SetSpeed(const float speed);

		void Draw(Graphics& gfx) const; 
		void Update(float dt);

		void BounceX();
		void BounceY();

		Rect GetRect() const;

	private:

		const float mRadius = 10.0f;
		float mSpeed = 300.0f;
		Vector2 mPos;
		Vector2 mDir;
		Color mColor;
};

