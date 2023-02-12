#pragma once

#include "Ball.h"
#include "Vector2.h"
#include "Rect.h"
#include "Color.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
	public:

		Paddle(const Vector2& pos_in, float halfWidth_in, float halfHeight_in);

		void Draw(Graphics& gfx) const;
		bool DoBallCollision(Ball& ball);
		void DoWallCollision(const Rect& walls);
		void Update(const Keyboard& kbd, float dt);
		Rect GetRect() const;

	private:

		Color mColor = Colors::White;
		const float mSpeed = 360.0f;

		// add variability to ball bounce behavior
		static constexpr float maximumExitRatio = 2.6f;
		static constexpr float fixedZoneWidthRatio = 0.2f;

		float halfWidth;
		float halfHeight;

		// these are derived from above controls
		float exitXFactor;
		float fixedZoneHalfWidth;
		float fixedZoneExitX;

		Vector2 pos;
		//bool isCooldown = false;
};