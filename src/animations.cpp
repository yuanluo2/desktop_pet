#include "animations.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace desktop_pet {
    Animations::Animations(SDL_Renderer* renderer, std::string const& configFilePath) {
        std::ifstream f{ configFilePath };
        json data = json::parse(f);
        framePaths.reserve(data.size());

        for (const auto&[action, values] : data.items()) {
            std::vector<std::string> paths;
            for (const auto& imgPath : values) {
                paths.emplace_back(imgPath.get<std::string>());
            }

            framePaths.emplace_back(std::move(paths));
        }

        load_current_character_resources(renderer);
    }

    void Animations::load_current_character_resources(SDL_Renderer* renderer) {
        frames.reset();

        for (const std::string& imgPath : framePaths[currentFrameGroupIndex]) {
            frames.add_new_frame(renderer, imgPath);
        }
    }

    void Animations::change_current_character(SDL_Renderer* renderer) {
        currentFrameGroupIndex = (currentFrameGroupIndex + 1) % framePaths.size();
        load_current_character_resources(renderer);
    }

    void Animations::update_current_character_frame() {
        frames.update();
    }

    void Animations::render_current_character_frame(SDL_Window* window, SDL_Renderer* renderer) {
        frames.render(window, renderer);
    }

    const FrameGroup& Animations::get_current() const noexcept {
        return frames;
    }
}
