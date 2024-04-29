#include "init_sdl.h"
#include <stdexcept>

using namespace std::string_literals;

namespace desktop_pet {
    InitSDL::InitSDL(Uint32 flags) {
        if (SDL_Init(flags) != 0) {
            throw std::runtime_error{ "SDL_Init() failed: "s + SDL_GetError() };
        }
    }

    InitSDL::~InitSDL() noexcept {
        SDL_Quit();
    }

    bool InitSDL::set_hint(std::string const& name, std::string const& value) noexcept {
        return SDL_SetHint(name.c_str(), value.c_str());
    }
}
