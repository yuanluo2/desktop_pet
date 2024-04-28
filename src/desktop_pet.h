#pragma once

#include <Windows.h>
#include <utility>
#include "constant.h"
#include "window.h"
#include "renderer.h"
#include "timer.h"
#include "encoding.h"
#include "popup_menu.h"
#include "extra_function.h"
#include "animations.h"

namespace desktop_pet {
    class DesktopPet {
        Window window;
        Renderer renderer;
        Timer timer;
        Animations animations;
        bool isUserClickMenu = false;
        bool running = true;

        HWND get_underlying_window_handle();
        std::pair<int, int> get_user_desktop_size();
        void set_background_transparent(HWND hwnd);
        void load_frames();
        void set_frame_position(Frame const& frame, int desktopWidth, int desktopHeight);
        void handle_menu_event(HWND hwnd, int desktopWidth, int desktopHeight);
    public:
        DesktopPet();
        ~DesktopPet() noexcept {}
        DesktopPet(DesktopPet const&) = delete;
        DesktopPet& operator=(DesktopPet const&) = delete;
        DesktopPet(DesktopPet &&) = delete;
        DesktopPet& operator=(DesktopPet &&) = delete;

        void show();
    };
}