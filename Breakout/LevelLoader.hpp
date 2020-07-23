#pragma once

#include <memory>
#include <string>
#include <vector>
#include "GameObject.hpp"
#include "Block.hpp"

namespace Breakout {

	/*
		Handles the loading of a level
	*/
	class LevelLoader {
	public:
		// Loads a specific level and fills the game objects list
		static bool LoadLevel(Game* game, std::string const& level, std::vector<GameObject*> &gos);
	};
}
