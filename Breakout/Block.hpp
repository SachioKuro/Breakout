#pragma once

#include "GameObject.hpp"

namespace Breakout {

	/*
		Represents a normal block without power-ups
	*/
	class Block : public GameObject {
	public:
		Block(Game* game, float x, float y, float size_w, float size_h, int sprite_set_idx, int lifes);

		virtual ~Block() {};

		void Render(Renderer*) const override;
		void Update(Action action) override;

		bool IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) override;

		virtual void OnDestroy() override;
	protected:
		// Size of the block
		float size_w, size_h;
		// Position of the texture in the texture map
		int sprite_set_idx;

		// Max durability of the block
		const int max_lifes;
		// Currant durabilty
		int lifes;
	}; 
}
