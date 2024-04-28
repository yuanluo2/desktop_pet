#pragma once

#include <SDL2/SDL.h>

namespace desktop_pet {
    class Renderer {
        SDL_Renderer* renderer = nullptr;
    public:
        Renderer(SDL_Window * window, int index, Uint32 flags);
        ~Renderer() noexcept;
        Renderer(Renderer&& other) noexcept;
        Renderer& operator=(Renderer&& other) noexcept;
        Renderer(Renderer const& other) = delete;
        Renderer& operator=(Renderer const& other) = delete;

        SDL_Renderer* get() noexcept;
    };
}