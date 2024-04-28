#pragma once

#include <Windows.h>

namespace desktop_pet {
    class PopupMenu {
        HMENU menu = nullptr;
    public:
        PopupMenu();
        ~PopupMenu() noexcept;
        PopupMenu(PopupMenu const&) = delete;
        PopupMenu& operator=(PopupMenu const&) = delete;
        PopupMenu(PopupMenu &&) = delete;
        PopupMenu& operator=(PopupMenu &&) = delete;
        
        WINBOOL wait_for_click(HWND parent, int x, int y);
    };
}