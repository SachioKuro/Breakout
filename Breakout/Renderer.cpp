#include "Renderer.hpp"
#include <iostream>
#include <string>
#include <algorithm>

#include "MovableGameObject.hpp"
#include "Paddle.hpp"

namespace Breakout {

	Renderer::Renderer(const std::size_t& screen_width, const std::size_t& screen_height)
		: screen_width(screen_width), screen_height(screen_height) {

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "SDL could not initialize.\n";
			std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
			return;
		}

		// Create Window
		sdl_window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, screen_width,
			screen_height, SDL_WINDOW_SHOWN);

		if (nullptr == sdl_window) {
			std::cerr << "Window could not be created.\n";
			std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
			return;
		}

		// Create renderer
		sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
		if (nullptr == sdl_renderer) {
			std::cerr << "Renderer could not be created.\n";
			std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
			return;
		}

		// Load texture map
		texture_map_image = IMG_Load("tiles_breakout.png");
		if (texture_map_image == nullptr) {
			std::cerr << "Texture map could not be loaded..\n";
			std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
			return;
		}

		texture_map = SDL_CreateTextureFromSurface(sdl_renderer, texture_map_image);
		SDL_FreeSurface(texture_map_image);

		SDL_SetTextureBlendMode(texture_map, SDL_BLENDMODE_BLEND);
	}

	Renderer::~Renderer() {
		SDL_DestroyWindow(sdl_window);
		SDL_Quit();
	}

	void Renderer::RenderStart() {
		SDL_SetRenderDrawColor(sdl_renderer, 0x5F, 0x1E, 0x1E, 0xFF);
		SDL_RenderClear(sdl_renderer);
	}

	template void Renderer::Render<Breakout::Paddle>(Breakout::Paddle& game_objects);
	template void Renderer::Render<Breakout::GameObject>(Breakout::GameObject& game_objects);
	template void Renderer::Render<Breakout::MovableGameObject>(Breakout::MovableGameObject& game_objects);

	template<typename T>
	void Renderer::Render(T& game_object) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		game_object.Render(this);
	}

	template void Renderer::Render<Breakout::GameObject>(std::vector<Breakout::GameObject*>& game_objects);
	template void Renderer::Render<Breakout::MovableGameObject>(std::vector<Breakout::MovableGameObject*>& game_objects);

	template<typename T>
	void Renderer::Render(std::vector<T*>& game_objects) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		std::for_each(game_objects.begin(), game_objects.end(), [this](GameObject* go) {go->Render(this); });
	}

	void Renderer::RenderEnd() {
		SDL_RenderPresent(sdl_renderer);
	}

	void Renderer::DrawFilledRect(float x, float y, float w, float h, int r, int g, int b, int a) {
		SDL_Rect rect{ x, y, w, h };
		SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
		SDL_RenderFillRect(sdl_renderer, &rect);
	}

	void Renderer::set_pixel(float x, float y, int r, int g, int b, int a) {
		SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
		SDL_RenderDrawPoint(sdl_renderer, x, y);
	}

	void Renderer::draw_circle(float n_cx, float n_cy, float radius, int r, int g, int b, int a) {
		// https://stackoverflow.com/questions/41524497/c-sdl2-rendering-a-circle/41570334

		double error = (double)-radius;
		double x = (double)radius - 0.5;
		double y = (double)0.5;
		double cx = n_cx - 0.5;
		double cy = n_cy - 0.5;

		while (x >= y) {
			set_pixel(cx + x, cy + y, r, g, b, a);
			set_pixel(cx + y, cy + x, r, g, b, a);

			if (x != 0) {
				set_pixel(cx - x, cy + y, r, g, b, a);
				set_pixel(cx + y, cy - x, r, g, b, a);
			}

			if (y != 0) {
				set_pixel(cx + x, cy - y, r, g, b, a);
				set_pixel(cx - y, cy + x, r, g, b, a);
			}

			if (x != 0 && y != 0) {
				set_pixel(cx - x, cy - y, r, g, b, a);
				set_pixel(cx - y, cy - x, r, g, b, a);
			}

			error += y;
			++y;
			error += y;

			if (error >= 0) {
				--x;
				error -= x;
				error -= x;
			}
		}
	}

	void Renderer::DrawFilledCircle(float x, float y, float radius, int r, int g, int b, int a) {
		// Note that there is more to altering the bitrate of this 
		// method than just changing this value.  See how pixels are
		// altered at the following web page for tips:
		//   http://www.libsdl.org/intro.en/usingvideo.html
		static const int BPP = 4;


		for (double dy = 1; dy <= radius; dy += 1.0) {
			double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
			SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
			SDL_RenderDrawLine(sdl_renderer, x - dx, y + dy - radius, x + dx, y + dy - radius);
			SDL_RenderDrawLine(sdl_renderer, x - dx, y - dy + radius, x + dx, y - dy + radius);
		}
	}

	void Renderer::DrawTexture(int x, int y, int width, int height, int tiles_x, int tiles_y) {
		SDL_Rect src{ tiles_x * tiles_width, tiles_y * tiles_height, tiles_width, tiles_height };
		SDL_Rect dst{ x, y, width, height };

		SDL_RenderCopy(sdl_renderer, texture_map, &src, &dst);
	}

}