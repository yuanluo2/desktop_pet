#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "frame_group.h"

namespace desktop_pet {
    class Animations {
        size_t currentFrameGroupIndex = 0;
        FrameGroup frames;
        std::vector<std::vector<std::string>> framePaths;

        void load_current_character_resources(SDL_Renderer* renderer);
    public:
        Animations(SDL_Renderer* renderer, std::string const& configFilePath);
        ~Animations() = default;
        Animations(Animations const&) = default;
        Animations& operator=(Animations const&) = default;
        Animations(Animations &&) = default;
        Animations& operator=(Animations &&) = default;

        void change_current_character(SDL_Renderer* renderer);
        void update_current_character_frame();
        void render_current_character_frame(SDL_Window* window, SDL_Renderer* renderer);
        const FrameGroup& get_current() const noexcept;
    };
}