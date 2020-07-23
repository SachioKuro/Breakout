#include "LevelLoader.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>

#include "Block_Ball.hpp"
#include "Game.hpp"

namespace fs = std::filesystem;

namespace Breakout {
	/*
		Infos about a block
	*/
	struct BlockInfo {
		int lifes;
		int idx;
		std::string type;
	};

	bool LevelLoader::LoadLevel(Game* game, std::string const& level, std::vector<GameObject*> &gos) {
		// Path of the level file
		fs::path path(level + ".level");
		if (fs::exists(path)) {
			std::cout << "File found\n";

			int block_w_per, block_h_per, space, offset_y, block_count_h, block_count_v, block_type_n;

			// Open the level file
			std::ifstream stream(path.c_str());

			// Loads the metadata
			if (!(stream >> block_w_per >> block_h_per >> space >> offset_y >> block_count_h >> block_count_v >> block_type_n)) {
				std::cout << "Malformed File" << std::endl;
				return false;
			}

			std::map<std::string, BlockInfo> block_infos{};

			float block_w = game->BoundsW() * (block_w_per / 100.f);
			float block_h = game->BoundsW() * (block_h_per / 100.f);
			float spacing_w = space;
			float spacing_h = spacing_w;
			float offset_x = (game->BoundsW() - (block_w * block_count_h) - (spacing_w * (block_count_h - 1))) / 2.f;

			// Read the available block types of the file
			for (auto i = 0; i < block_type_n; ++i) {
				BlockInfo info;
				if (!(stream >> info.type >> info.lifes >> info.idx)) {
					std::cout << "Malformed File" << std::endl;
					return false;
				}
				block_infos[info.type] = info;
			}

			// Fill the level with the block
			for (auto j = 0; j < block_count_v; ++j) {
				for (auto i = 0; i < block_count_h; ++i) {
					std::string t;
					if (!(stream >> t)) {
						std::cout << "Malformed File" << std::endl;
						return false;
					}
					std::cout << t << " ";

					try {
						if (t == "bb")
							gos.emplace_back(new Block_Ball(game, offset_x + block_w * i + spacing_w * i, offset_y + block_h * j + spacing_h * j, block_w, block_h, block_infos[t].idx, block_infos[t].lifes));
						else
							gos.emplace_back(new Block(game, offset_x + block_w * i + spacing_w * i, offset_y + block_h * j + spacing_h * j, block_w, block_h, block_infos[t].idx, block_infos[t].lifes));
					} catch(const std::out_of_range &oor) {
						std::cout << "Malformed File" << std::endl;
						return false;
					}
				}
				std::cout << std::endl;
			}

			return true;
		} else {
			std::cout << "File not found" << std::endl;
			return false;
		}
	}
}