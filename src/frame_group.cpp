#include "frame_group.h"

namespace desktop_pet {
    void FrameGroup::add_new_frame(SDL_Renderer* renderer, std::string const& imgPath) {
        frames.emplace_back(renderer, imgPath);
    }

    Frame const& FrameGroup::get_frame(size_t index) const noexcept {
        return frames[index];
    }

    void FrameGroup::update() {
        currentFrame = (currentFrame + 1) % frames.size();
    }

    void FrameGroup::render(SDL_Window* window, SDL_Renderer* renderer) {
        frames[currentFrame].render(window, renderer);
    }
}