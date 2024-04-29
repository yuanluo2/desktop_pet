#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "frame.h"

namespace desktop_pet {
    class FrameGroup {
        std::vector<Frame> frames;
        size_t currentFrame = 0;
    public:
        void reset() noexcept;
        void add_new_frame(SDL_Renderer* renderer, std::string const& imgPath);
        Frame const& get_frame(size_t index) const noexcept;
        void update();
        void render(SDL_Window* window, SDL_Renderer* renderer);
    };
}