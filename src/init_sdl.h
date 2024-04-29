#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace desktop_pet {
    class InitSDL {
    public:
        InitSDL(Uint32 flags);
        ~InitSDL() noexcept;
        InitSDL(InitSDL const&) = delete;
        InitSDL& operator=(InitSDL const&) = delete;
        InitSDL(InitSDL &&) = delete;
        InitSDL& operator=(InitSDL &&) = delete;

        bool set_hint(std::string const& name, std::string const& value) noexcept;
    };
}
