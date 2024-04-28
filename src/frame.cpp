#include "frame.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace desktop_pet {
    Frame::Frame(SDL_Renderer* renderer, std::string const& imgPath) {
        SDL_Surface* surf = IMG_Load(imgPath.c_str());
        if (surf == nullptr) {
            throw std::runtime_error{ "Load "s + imgPath + " failed, error: "s + IMG_GetError() };
        }

        width = surf->w;
        height = surf->h;

        tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        if (tex == nullptr) {
            throw std::runtime_error{ "create texture from "s + imgPath + " failed, error: "s + SDL_GetError() };
        }
    }

    Frame::~Frame() noexcept {
        if (tex != nullptr) {
            SDL_DestroyTexture(tex);
            width = 0;
            height = 0;
        }
    }

    Frame::Frame(Frame&& other) noexcept {
        if (this != &other) {
            std::swap(tex, other.tex);
            std::swap(width, other.width);
            std::swap(height, other.height);
        }
    }

    Frame& Frame::operator=(Frame&& other) noexcept {
        if (this != &other) {
            std::swap(tex, other.tex);
            std::swap(width, other.width);
            std::swap(height, other.height);
        }

        return *this;
    }

    int Frame::get_width() const noexcept {
        return width;
    }

    int Frame::get_height() const noexcept {
        return height;
    }

    void Frame::render(SDL_Window* window, SDL_Renderer* renderer) noexcept {
        SDL_SetRenderDrawColor(renderer, 197, 187, 57, 0);
        SDL_RenderClear(renderer);

        // window's size will always change to the image's size.
        SDL_SetWindowSize(window, width, height);
        
        SDL_Rect renderRect = { 0, 0, width, height };
        SDL_RenderCopy(renderer, tex, nullptr, &renderRect);
        SDL_RenderPresent(renderer);
    }
}
