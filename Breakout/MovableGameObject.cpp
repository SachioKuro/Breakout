#include "MovableGameObject.hpp"

namespace Breakout {
	void MovableGameObject::Collide(float x_normal, float y_normal) {
		// Set the position one step back
		this->x_pos -= this->velocity_x * this->velocity_multi;
		this->y_pos -= this->velocity_y * this->velocity_multi;

		// Normalize the normals
		float norm = sqrtf(x_normal * x_normal + y_normal * y_normal);
		x_normal /= norm;
		y_normal /= norm;

		// Calculates the ne velocities
 		float dot_ri_n = this->velocity_x * x_normal + this->velocity_y * y_normal;
		this->velocity_x = -2 * x_normal * dot_ri_n + this->velocity_x;
		this->velocity_y = -2 * y_normal * dot_ri_n + this->velocity_y;

		// Correct the position after the collision
		this->x_pos += this->velocity_x * this->velocity_multi;
		this->y_pos += this->velocity_y * this->velocity_multi;
	}

	void MovableGameObject::IncVelocityMultiByPer(float per) {
		velocity_multi += per;
	}

	void MovableGameObject::update_position() {
		this->x_pos += this->velocity_x * this->velocity_multi;
		this->y_pos += this->velocity_y * this->velocity_multi;
	}
}