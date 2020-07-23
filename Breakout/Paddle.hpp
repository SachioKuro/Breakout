#pragma once

#include "GameObject.hpp"

namespace Breakout {

	/*
		Represents the player
	*/
	class Paddle : public GameObject {
	public:
		Paddle(Game* game, float size_w, float size_h, Color color);

		void Render(Renderer*) const override;
		void Update(Action action) override;

		bool IntersectsWith(GameObject* obj, float* x_normal_out, float* y_normal_out) override;

		virtual void OnDestroy() override;
	private:
		float velocity = 0;
		int delta_t = 0;
		float size_w;
		float size_h;
		float size_multi;
		
		int lifes;
	};
}
