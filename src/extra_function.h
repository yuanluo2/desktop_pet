#pragma once

#include <SDL2/SDL.h>

namespace desktop_pet {
    /**
     * The SDL timer callback, just send a SDL_USEREVENT event to the SDL events queue.
    */
    Uint32 send_user_event_callback(Uint32 interval, void* param);
}