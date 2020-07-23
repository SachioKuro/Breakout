#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"


namespace Breakout {
    class GameObject;

    /*
        Handles the rendering
    */
    class Renderer {
    public:
        Renderer(const std::size_t& screen_width, const std::size_t& screen_height);
        ~Renderer();

        // Start rendering
        void RenderStart();

        // Render a game object
        template<typename T>
        void Render(T &game_object);
        // Render a list of game objects
        template<typename T>
        void Render(std::vector<T*> &game_objects);

        // Commit rendering
        void RenderEnd();

        void DrawFilledRect(float x, float y, float w, float h, int r, int g, int b, int a);
        void DrawFilledCircle(float x, float y, float radius, int r, int g, int b, int a);

        void DrawTexture(int x, int y, int width, int height, int tiles_x, int tiles_y);
    private:
        SDL_Window* sdl_window;
        SDL_Renderer* sdl_renderer;

        // Texture map stuff
        SDL_Surface* texture_map_image;
        SDL_Texture* texture_map;
        const std::size_t tiles_width = 332;
        const std::size_t tiles_height = 166;

        const std::size_t screen_width;
        const std::size_t screen_height;

        void set_pixel(float x, float y, int r, int g, int b, int a);
        void draw_circle(float n_cx, float n_cy, float radius, int r, int g, int b, int a);
    };
}
