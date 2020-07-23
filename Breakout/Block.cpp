#include "Block.hpp"

#include <algorithm>
#include "Game.hpp"

namespace Breakout {
	Block::Block(Game* game, float x, float y, float size_w, float size_h, int sprite_set_idx, int lifes)
		: GameObject(game, x, y, Color{}), size_w(size_w), size_h(size_h), sprite_set_idx(sprite_set_idx), lifes(lifes), max_lifes(lifes) {}

	void Block::Render(Renderer* renderer) const {
		renderer->DrawTexture(x_pos, y_pos, size_w, size_h, sprite_set_idx, max_lifes - lifes);
	}

	void Block::Update(Action action) {
		switch (action) {
		// Something hit the block
		case Action::hit:
			// Makes sure the block handles the hit only one time per frame
			if (collision_detected) {
				lifes--;
				collision_detected = false;
			}

			if (lifes <= 0) {
				this->alive = false;
			}
			break;
		default:
			break;
		}
	}

	bool Block::IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) {
		if (obj->IntersectsLine(x_pos, y_pos, x_pos + size_w, y_pos)) {
			*x_normal_out = 0.f;
			*y_normal_out = 1.f;
			return true;
		}
		else if (obj->IntersectsLine(x_pos, y_pos + size_h, x_pos + size_w, y_pos + size_h)) {
			*x_normal_out = 0.f;
			*y_normal_out = -1.f;
			return true;
		}
		else if (obj->IntersectsLine(x_pos, y_pos, x_pos, y_pos + size_h)) {
			*x_normal_out = -1.f;
			*y_normal_out = 0.f;
			return true;
		}
		else if (obj->IntersectsLine(x_pos + size_w, y_pos, x_pos + size_w, y_pos + size_h)) {
			*x_normal_out = 1.f;
			*y_normal_out = 0.f;
			return true;
		}

		return false;
	}

	void Block::OnDestroy() {
		game->Update(GameObject::Action::block_destroyed);
	}

}
