#pragma once

#include <memory>
#include "Renderer.hpp"

namespace Breakout {
	// Forward declaration
	class Game;

	// Display Color
	struct Color {
		int r, g, b, a;
	};

	/*
		Virtual class for all entities
	*/
	class GameObject {
	public:
		// Messages for communication between components
		enum class Action { 
			left, 
			right, 
			bump, 
			cancel, 
			hit, 
			hit_ground, 
			start, 
			update, 
			block_destroyed, 
			block_ball_destroyed, 
			ball_destroyed 
		};

		GameObject(Game* game, float x_pos, float y_pos, Color color)
			: x_pos(x_pos), y_pos(y_pos), color(color), game(game) {};

		virtual ~GameObject() {};

		float X() const {
			return x_pos;
		}

		void X(float x) {
			x_pos = x;
		}

		float Y() const {
			return y_pos;
		}

		void Y(float y) {
			y_pos = y;
		}


		bool CollisionDetected() const { 
			return collision_detected; 
		};

		void CollisionDetected(bool collision_detected) { 
			this->collision_detected = collision_detected; 
		};

		// ################### Virtual Methods ###################

		// Defines how the object should rendered on screen
		virtual void Render(Renderer* renderer) const = 0;

		// Defines how the object should updated, for an particular action
		virtual void Update(Action action) = 0;

		// Collision detection methods
		virtual bool IntersectsLine(float x1, float y1, float x2, float y2) { return false; };
		virtual bool IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) = 0;

		// Called on destruction of the object (Could do this in the destructor, but wanted to separate the game logic) 
		virtual void OnDestroy() = 0;

		// Return true if the object is still alive, false otherwise
		bool isAlive() const { return alive; }
	protected:
		// Color of the entity
		Color color;

		// Position of the entity
		float x_pos, y_pos;

		// Entire Game-Handle
		Game* game;

		// Is the entity is alive 
		bool alive = true;
		// Was a collision detected
		bool collision_detected = false;
	};
}