#pragma once

#include <vector>
#include <random>
#include <string>
#include <SDL2/SDL.h>
#include "frame_group.h"

namespace desktop_pet {
    class Animations {
        std::mt19937 gen{ std::random_device{}() };
        std::uniform_int_distribution<size_t> distrib;
        size_t currentFrameGroupIndex = 0;
        std::vector<FrameGroup> frameGroups;
    public:
        void init_size(size_t size);
        void add_frame_at(size_t index, SDL_Renderer* renderer, std::string const& imgPath);
        void random_change_current_frames();
        void update_current_frames();
        void render_current_frames(SDL_Window* window, SDL_Renderer* renderer);
        const FrameGroup& get_current() const noexcept;
    };
}