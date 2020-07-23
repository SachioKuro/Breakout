#include "Game.hpp"

#include <iostream>
#include <algorithm>
#include "SDL.h"

#include "LevelLoader.hpp"

namespace Breakout {
    Game::Game(float bounds_w, float bounds_h) : bounds_w(bounds_w), bounds_h(bounds_h) {
        // Create player
        _paddle = new Paddle(this, 75, 20, Color{ 0x20, 0x00, 0xda, 0xff });
        // Create list with starting ball
        _balls.emplace_back(new Ball(this, 10, Color{ 0xda, 0x00, 0x20, 0xff }));

        // Load the level
        LevelLoader::LoadLevel(this, "01", _bricks);
    }

    Game::~Game() {
        for (auto& ball : _balls)
            delete ball;
        for (auto& brick : _bricks)
            delete brick;
        delete _paddle;
    }

    float Game::BoundsW() {
        return bounds_w;
    }

    float Game::BoundsH() {
        return bounds_h;
    }

    void Game::Update(GameObject::Action action) {
        switch (action)
        {
        case GameObject::Action::block_destroyed:
            // If a block is destroyed, tell the balls
            std::for_each(this->_balls.begin(), this->_balls.end(), [](MovableGameObject* ball) { ball->Update(GameObject::Action::block_destroyed); });
            break;
        case GameObject::Action::block_ball_destroyed:
            // If a ball-block is destroyed, tell the balls
            std::for_each(this->_balls.begin(), this->_balls.end(), [](MovableGameObject* ball) { ball->Update(GameObject::Action::block_destroyed); });
            // Create 3 new Balls and activate them
            for (auto i = 0; i < 3; ++i) {
                _balls.emplace_back(new Ball(this, 10, Color{ 0xda, 0x00, 0x20, 0xff }));
                _balls.back()->Update(GameObject::Action::start);
            }
            break;
        case GameObject::Action::ball_destroyed:
            // Not used yet
            break;
        default:
            break;
        }
    }

    void Game::Run(std::unique_ptr<Controller> controller, std::unique_ptr<Renderer> renderer, std::unique_ptr<Physics> physics, std::size_t target_frame_duration) {
        // Time / Frame control
        Uint32 title_timestamp = SDL_GetTicks();
        Uint32 frame_start;
        Uint32 frame_end;
        Uint32 frame_duration;
        int frame_count = 0;

        // Is the game running
        bool running = true;

        // Activate the balls
        std::for_each(_balls.begin(), _balls.end(), [](MovableGameObject* go) { go->Update(GameObject::Action::start); });

        while (running) {
            frame_start = SDL_GetTicks();

            // Handles user input
            controller->HandleInput(running, _paddle);

            // Check collisions of the balls with the game bounderies
            physics->CheckMovableCollision(this, _balls);
            // Check collisions of the balls with the player
            physics->CheckMovableCollision(this, _balls, *_paddle);
            // Check collisions of the balls with the blocks
            physics->CheckMovableCollision(this, _balls, _bricks);

            // Update blocks
            std::for_each(_bricks.begin(), _bricks.end(), [](GameObject* go) { go->Update(GameObject::Action::update); });
            // Update balls
            std::for_each(_balls.begin(), _balls.end(), [](MovableGameObject* go) { go->Update(GameObject::Action::update); });
            // Update player
            _paddle->Update(GameObject::Action::update);

            // Delete dead game objects
            _balls.erase(std::remove_if(_balls.begin(), _balls.end(), [](MovableGameObject* go) { return !go->isAlive(); }), _balls.end());
            _bricks.erase(std::remove_if(_bricks.begin(), _bricks.end(), [](GameObject* go) {
                bool isDead = !go->isAlive();

                // Trigger block specific destruction method
                if (isDead)
                    go->OnDestroy();

                return isDead;
            }), _bricks.end());

            // Check if you lost
            if (_balls.empty()) {
                running = false;
                std::cout << "You lost! :(" << std::endl;
            }

            // Check if you won
            if (_bricks.empty()) {
                running = false;
                std::cout << "You won! :)" << std::endl;
            }

            // Render all the things
            renderer->RenderStart();
            renderer->Render(*_paddle);
            renderer->Render<MovableGameObject>(_balls);
            renderer->Render<GameObject>(_bricks);
            renderer->RenderEnd();

            frame_end = SDL_GetTicks();

            frame_duration = frame_end - frame_start;

            if (frame_duration < target_frame_duration) {
                SDL_Delay(target_frame_duration - frame_duration);
            }
        }
    }
}