#include "Controller.hpp"

#include <iostream>
#include "SDL.h"

void Breakout::Controller::Init() {
	//SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL)
}

void Breakout::Controller::HandleInput(bool& running, GameObject* game_object) {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				game_object->Update(GameObject::Action::left);
				break;
			case SDLK_RIGHT:
				game_object->Update(GameObject::Action::right);
				break;
			case SDLK_UP:
				// Not used atm
				game_object->Update(GameObject::Action::bump);
				break;
			default:
				break;
			}
		}
		else if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_RIGHT:
				std::cout << "Key Up\n";
				game_object->Update(GameObject::Action::cancel);
				break;
			default:
				break;
			}
		}
	}
}
