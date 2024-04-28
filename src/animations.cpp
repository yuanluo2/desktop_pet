#include "animations.h"

namespace desktop_pet {
    void Animations::init_size(size_t size) {
        frameGroups.resize(size);
        distrib = std::uniform_int_distribution<size_t>(0, size - 1);
        random_change_current_frames();
    }

    void Animations::add_frame_at(size_t index, SDL_Renderer* renderer, std::string const& imgPath) {
        frameGroups[index].add_new_frame(renderer, imgPath);
    }

    void Animations::random_change_current_frames() {
        size_t newFrame;

        do {
            newFrame = distrib(gen);
        } while (newFrame == currentFrameGroupIndex);

        currentFrameGroupIndex = newFrame;
    }

    void Animations::update_current_frames() {
        frameGroups[currentFrameGroupIndex].update();
    }

    void Animations::render_current_frames(SDL_Window* window, SDL_Renderer* renderer) {
        frameGroups[currentFrameGroupIndex].render(window, renderer);
    }

    const FrameGroup& Animations::get_current() const noexcept {
        return frameGroups[currentFrameGroupIndex];
    }
}
