#pragma once

#include <memory>
#include "GameObject.hpp"

namespace Breakout {

	/*
		Virtual class for all self moving entities
	*/
	class MovableGameObject : public GameObject {
	public:
		MovableGameObject(Game* game, float x_pos, float y_pos, Color color)
			: GameObject(game, x_pos, y_pos, color) {};

		virtual ~MovableGameObject() {};

		// Handles a collision
		void Collide(float x_normal, float y_normal);

		bool IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) override {
			return false;
		}

		// Increaes the velocity by a percentage
		void IncVelocityMultiByPer(float per);

		float VelocityX() const {
			return velocity_x;
		}

		void VelocityX(float velo_x) {
			velocity_x = velo_x;
		}

		float VelocityY() const {
			return velocity_y;
		}

		void VelocityY(float velo_y) {
			velocity_y = velo_y;
		}

	protected:
		// Update the postion of the movable object
		void update_position();

		float velocity_x = 0.f;
		float velocity_y = 0.f;
		float velocity_multi = 3.f;
		int delta_t = 0;
	};
}
