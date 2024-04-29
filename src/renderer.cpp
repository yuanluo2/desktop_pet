#include "renderer.h"
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace desktop_pet {
    Renderer::Renderer(SDL_Window * window, int index, Uint32 flags) {
        if ((renderer = SDL_CreateRenderer(window, index, flags)) == nullptr) {
            throw std::runtime_error{ "SDL_CreateRenderer() failed: "s + SDL_GetError() };
        }
    }

    Renderer::~Renderer() noexcept {
        if (renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
        }
    }

    Renderer::Renderer(Renderer&& other) noexcept {
        if (this != &other) {
            std::swap(renderer, other.renderer);
        }
    }

    Renderer& Renderer::operator=(Renderer&& other) noexcept {
        if (this != &other) {
            std::swap(renderer, other.renderer);
        }

        return *this;
    }

    SDL_Renderer* Renderer::get() noexcept {
        return renderer;
    }
}