#pragma once

#include <memory>

#include "Controller.hpp"
#include "Renderer.hpp"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "MovableGameObject.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "Ball.hpp"

namespace Breakout {

	/*
		Central Component which handles updates and the main game loop
	*/
	class Game {
	public:
		Game(float bounds_w, float bound_h);
		~Game();

		float BoundsW();
		float BoundsH();

		// Defines how the game should updated, for an particular action
		void Update(GameObject::Action action);

		// Starts the main game loop
		void Run(std::unique_ptr<Controller> controller, std::unique_ptr<Renderer> renderer, std::unique_ptr<Physics> physics, std::size_t target_frame_duration);
	private:
		// Size of window
		float bounds_w, bounds_h;

		// Player
		Paddle* _paddle;
		std::vector<GameObject*> _bricks{};
		std::vector<MovableGameObject*> _balls{};
	};
}