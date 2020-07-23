#include "Paddle.hpp"

#include <iostream>
#include <algorithm>
#include "Game.hpp"

namespace Breakout {
	Paddle::Paddle(Game* game, float size_w, float size_h, Color color)
		: GameObject(game, game->BoundsW() / 2, game->BoundsH() - 50, color), size_w(size_w), size_h(size_h), size_multi(1.f), lifes(3) {}

	void Paddle::Render(Renderer* renderer) const {
		renderer->DrawFilledRect(x_pos, y_pos, size_w * size_multi, size_h, this->color.r, this->color.g, this->color.b, this->color.a);
	}

	void Paddle::Update(Action action) {
		static int dir = 0;
		static int prev_dir = 0;
		static float oldV = 0;
		switch (action) {
		case Breakout::GameObject::Action::cancel:
			dir = 0;
			break;
		case Breakout::GameObject::Action::left:
			if (dir != 1) dir = -1;
			break;
		case Breakout::GameObject::Action::right:
			if (dir != -1) dir = 1;
			break;
		case Breakout::GameObject::Action::bump:
			break;
		case Breakout::GameObject::Action::update:
			// A rookie attemp to smooth the movement
			delta_t++;
			if (dir == 0 || dir != prev_dir) {
				velocity = 0;
				delta_t = 0;
			}
			prev_dir = dir;
			oldV = velocity;
			velocity = std::min(oldV + .75f * delta_t, 1.f);
			x_pos += dir * ((velocity + oldV) / 2 * delta_t);
			x_pos = std::clamp(x_pos, 0.f, static_cast<float>(game->BoundsW() - size_w));
			break;
		default:
			break;
		}
	}

	bool Paddle::IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) {
		if (obj->IntersectsLine(x_pos, y_pos, x_pos + size_w, y_pos)) {
			*x_normal_out = 0.f;
			*y_normal_out = 1.f;
			return true;
		} else if (obj->IntersectsLine(x_pos, y_pos + size_h, x_pos + size_w, y_pos + size_h)) {
			*x_normal_out = 0.f;
			*y_normal_out = -1.f;
			return true;
		} else if (obj->IntersectsLine(x_pos, y_pos, x_pos, y_pos + size_h)) {
			*x_normal_out = -1.f;
			*y_normal_out = 0.f;
			return true;
		} else if (obj->IntersectsLine(x_pos + size_w, y_pos, x_pos + size_w, y_pos + size_h)) {
			*x_normal_out = 1.f;
			*y_normal_out = 0.f;
			return true;
		}

		return false;
	}

	void Paddle::OnDestroy() {
	}
}