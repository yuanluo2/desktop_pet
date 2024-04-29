#include "init_sdl.h"
#include "init_img.h"
#include "desktop_pet.h"
#include <iostream>

#undef main

int main() {
    using namespace desktop_pet;

    try{
        InitSDL initSDL{ SDL_INIT_VIDEO };
        InitIMG initIMG{ IMG_INIT_PNG };

        initSDL.set_hint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        /**
         * It's very important to set this hint here.
         * 
         * If we click somewhere, this window will lost focus, later when we drag the window, 
         * the '''SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH''' hint can make sure that the window will be draged and moved as expected.
         * 
         * without this hint, after lost focus, you may find that you can never drag the window unless you click the window first, 
         * because the click action is just to gain the focus. but actually drag action has already contain the click action, 
         * it's really meaningless and strange to do the extra click, also that's really bad for user's experience.
        */
        initSDL.set_hint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

        DesktopPet hm;
        hm.show();
    } catch(std::exception const& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
