#include "window.h"
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace desktop_pet {
    Window::Window(std::string const& title, int x, int y, int w, int h, Uint32 flags) {
        if ((window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) == nullptr) {
            throw std::runtime_error{ "SDL_CreateWindow() failed: "s + SDL_GetError() };
        }
    }

    Window::~Window() noexcept {
        if (window != nullptr) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }

    Window::Window(Window&& other) noexcept {
        if (this != &other) {
            std::swap(window, other.window);
        }
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this != &other) {
            std::swap(window, other.window);
        }

        return *this;
    }

    SDL_Window* Window::get() noexcept {
        return window;
    }
}
