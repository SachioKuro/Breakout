#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "MovableGameObject.hpp"

namespace Breakout {
	class Game;

	/*
		Handles the physics, in our case only the collition detection
	*/
	class Physics {
	public:
		Physics();

		// Handles collition of movable objects with the game boundings
		void CheckMovableCollision(Game* game, std::vector<MovableGameObject*>& objs);
		// Handles collition of movable objects with a game object
		void CheckMovableCollision(Game* game, std::vector<MovableGameObject*>& objs, GameObject& go);
		// Handles collition of movable objects with a list of game objects
		void CheckMovableCollision(Game* game, std::vector<MovableGameObject*>& objs, std::vector<GameObject*>& gos);
	private:
	};
}
