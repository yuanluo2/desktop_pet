#pragma once

#include <SDL2/SDL_image.h>

namespace desktop_pet {
    class InitIMG {
    public:
        InitIMG(int flags);
        ~InitIMG() noexcept;

        InitIMG(InitIMG const&) = delete;
        InitIMG& operator=(InitIMG const&) = delete;
        InitIMG(InitIMG &&) = delete;
        InitIMG& operator=(InitIMG &&) = delete;
    };
}
