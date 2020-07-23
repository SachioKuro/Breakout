#include <iostream>
#include <memory>
#include "Controller.hpp"
#include "Renderer.hpp"
#include "Physics.hpp"
#include "Game.hpp"
#undef main

int main() {
	constexpr std::size_t kFPS{ 60 };
	constexpr std::size_t kMsPerFrame{ 1000 / kFPS };
	constexpr std::size_t kScreenWidth{ 400 };
	constexpr std::size_t kScreenHeight{ 600 };

	std::unique_ptr<Breakout::Renderer> renderer = std::make_unique<Breakout::Renderer>(kScreenWidth, kScreenHeight);
	std::unique_ptr<Breakout::Physics> physics = std::make_unique<Breakout::Physics>();
	std::unique_ptr<Breakout::Controller> controller = std::make_unique<Breakout::Controller>();
	Breakout::Game game(kScreenWidth, kScreenHeight);

	game.Run(std::move(controller), std::move(renderer), std::move(physics), kMsPerFrame);

	return 0;
}