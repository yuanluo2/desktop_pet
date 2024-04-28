#include "extra_function.h"

namespace desktop_pet {
    Uint32 send_user_event_callback(Uint32 interval, void* param) {
        bool isUserClickMenu = *(bool*)param;

        if (!isUserClickMenu) {
            SDL_Event event;
            event.type = SDL_USEREVENT;
            SDL_PushEvent(&event);
        }

        return interval;
    }
}