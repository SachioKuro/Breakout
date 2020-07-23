#pragma once

#include <memory>

#include "GameObject.hpp"

namespace Breakout {

	/*
		Handles the input
	*/
	class Controller {
	public:
		void Init();
		static void HandleInput(bool& running, GameObject* game_object);
	};
}

