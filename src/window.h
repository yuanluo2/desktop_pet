#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace desktop_pet {
    class Window {
        SDL_Window* window = nullptr;
    public:
        Window(std::string const& title, int x, int y, int w, int h, Uint32 flags);
        ~Window() noexcept;
        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;
        Window(Window const& other) = delete;
        Window& operator=(Window const& other) = delete;

        SDL_Window* get() noexcept;
    };
}
