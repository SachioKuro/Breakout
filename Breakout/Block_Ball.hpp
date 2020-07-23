#pragma once

#include "Block.hpp"

namespace Breakout {

	/*
		Represents a block wich spawns new balls on destruction
	*/
	class Block_Ball : public Block {
	public:
		Block_Ball(Game* game, float x, float y, float size_w, float size_h, int sprite_set_idx, int lifes);

		virtual ~Block_Ball() {};

		virtual void OnDestroy() override;
	};
}
