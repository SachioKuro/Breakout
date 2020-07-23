#include "Ball.hpp"

#include <algorithm>
#include <iostream>
#include "Game.hpp"

namespace Breakout {
	Ball::Ball(Game* game, float size, Color color)
		: MovableGameObject(game, game->BoundsW() / 2, game->BoundsH() - 100, color), 
		  engine(dev()), random_alpha(0, 360 * M_PI / 180),
		  size(size) {}

	Ball::Ball(Game* game, float size, Color color, float x, float y)
		: Ball(game, size, color) {
		
		this->X(x);
		this->Y(y);
	}

	void Ball::Render(Renderer* renderer) const {
		renderer->DrawFilledCircle(x_pos, y_pos, size, this->color.r, this->color.g, this->color.b, this->color.a);
	}

	void Ball::Update(Action action) {
		switch (action) {
		// Activate the ball
		case Breakout::GameObject::Action::start:
			// Choose random angle
			alpha = random_alpha(engine);
			// Initialize the x- and y-velocities
			velocity_x = cosf(alpha);
			velocity_y = sinf(alpha);
			break;
		// Update the ball
		case Breakout::GameObject::Action::update:
			update_position();
			break;
		// A block was destroyed
		case Breakout::GameObject::Action::block_destroyed:
			// Increases the speed of the ball
			this->IncVelocityMultiByPer(1.01);
			break;
		// Ball hit the ground
		case Breakout::GameObject::Action::hit_ground:
			this->alive = false;
			break;
		default:
			break;
		}
	}

	bool Ball::pointInCirlce(float x, float y) {
		float d_x = x - x_pos;
		float d_y = y - y_pos;
		float dist = sqrt(d_x * d_x + d_y * d_y);

		return dist <= size;
	}

	bool Ball::pointOnLine(float px, float py, float x1, float y1, float x2, float y2) {
		float dist_1 = sqrt((x1 - px) * (x1 - px) + (y1 - py) * (y1 - py));
		float dist_2 = sqrt((x2 - px) * (x2 - px) + (y2 - py) * (y2 - py));

		float line_length = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		float eps = .01f;

		return dist_1 + dist_2 >= line_length - eps && dist_1 + dist_2 <= line_length + eps;
	}

	bool Ball::IntersectsLine(float x1, float y1, float x2, float y2) {
		if (pointInCirlce(x1, y1) || pointInCirlce(x2, y2))
			return true;

		float line_length = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

		float dot_line_circle = ((x_pos - x1) * (x2 - x1) + (y_pos - y1) * (y2 - y1)) / (line_length * line_length);

		float closest_x = x1 + dot_line_circle * (x2 - x1);
		float closest_y = y1 + dot_line_circle * (y2 - y1);

		if (!pointOnLine(closest_x, closest_y, x1, y1, x2, y2))
			return false;

		float dist_x = closest_x - x_pos;
		float dist_y = closest_y - y_pos;
		return  sqrt(dist_x * dist_x + dist_y * dist_y) <= size;
	}

	void Ball::OnDestroy() {
		game->Update(GameObject::Action::ball_destroyed);
	}
}