#include "Block_Ball.hpp"

#include <algorithm>
#include "Game.hpp"
#include "Ball.hpp"

namespace Breakout {
	Block_Ball::Block_Ball(Game* game, float x, float y, float size_w, float size_h, int sprite_set_idx, int lifes)
		: Block(game, x, y, size_w, size_h, sprite_set_idx, lifes) {};

	void Block_Ball::OnDestroy() {
		game->Update(GameObject::Action::block_ball_destroyed);
	}
}
