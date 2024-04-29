#include "timer.h"
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace desktop_pet {
    Timer::Timer(Uint32 interval, SDL_TimerCallback callback, void *param) {
        if ((tid = SDL_AddTimer(interval, callback, param)) == 0) {
            throw std::runtime_error{ "SDL_AddTimer() failed: "s + SDL_GetError() };
        }
    }

    Timer::~Timer() noexcept {
        if (tid != 0) {
            SDL_RemoveTimer(tid);
        }
    }
}