#pragma once

#include <SDL2/SDL.h>

namespace desktop_pet {
    class Timer {
        SDL_TimerID tid = 0;
    public:
        Timer(Uint32 interval, SDL_TimerCallback callback, void *param);
        ~Timer() noexcept;

        Timer(Timer const&) = delete;
        Timer& operator=(Timer const&) = delete;
        Timer(Timer &&) = delete;
        Timer& operator=(Timer &&) = delete;
    };
}
