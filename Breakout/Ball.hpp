#pragma once

#include <random>
#include <memory>
#include <vector>
#include "MovableGameObject.hpp"

namespace Breakout {

	/*
		Represents the playing ball
	*/
	class Ball : public MovableGameObject {
	public:
		Ball(Game* game, float size, Color color);
		Ball(Game* game, float size, Color color, float x, float y);

		void Render(Renderer*) const override;
		void Update(Action action) override;

		bool IntersectsLine(float x1, float y1, float x2, float y2) override;

		virtual void OnDestroy() override;
	private:
		// Angle in which the ball is moving
		float alpha = 0.f;
		// Size of the ball
		float size;

		// Random stuff
		std::random_device dev;
		std::mt19937 engine;
		std::uniform_real_distribution<float> random_alpha;

		// Checks if a point is in a circle
		bool pointInCirlce(float x, float y);
		// Checks if a point is on a line
		bool pointOnLine(float px, float py, float x1, float y1, float x2, float y2);
	};
}