#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace desktop_pet {
    class Frame {
        SDL_Texture* tex = nullptr;
        int width = 0;
        int height = 0;
    public:
        Frame() = default;
        Frame(SDL_Renderer* renderer, std::string const& imgPath);
        ~Frame() noexcept;
        Frame(Frame&& other) noexcept;
        Frame& operator=(Frame&& other) noexcept;
        Frame(Frame const& other) = delete;
        Frame& operator=(Frame const& other) = delete;

        int get_width() const noexcept;
        int get_height() const noexcept;
        void render(SDL_Window* window, SDL_Renderer* renderer) noexcept;
    };
}