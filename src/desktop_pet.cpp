#include "desktop_pet.h"
#include <SDL2/SDL_syswm.h>
#include <fstream>
#include <string>

using namespace std::string_literals;

namespace desktop_pet {
    DesktopPet::DesktopPet()  :
        window{ "Desktop Pet", 0, 0, 0, 0, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS },
        renderer{ window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC },
        timer{ PET_FRAME_UPDATE_MILLISEC, send_user_event_callback, &isUserClickMenu },
        animations{ renderer.get(), "res\\animation.json" }
    {}

    HWND DesktopPet::get_underlying_window_handle() {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(window.get(), &wmInfo);
        return wmInfo.info.win.window;
    }

    void DesktopPet::set_background_transparent(HWND hwnd) {
        COLORREF colorKey = RGB(0, 0, 0);
        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hwnd, colorKey, 0, LWA_COLORKEY);
    }

    std::pair<int, int> DesktopPet::get_user_desktop_size() {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        auto userDesktopWidth = dm.w;
        auto userDesktopHeight = dm.h;

        return { userDesktopWidth, userDesktopHeight };
    }

    void DesktopPet::set_frame_position(Frame const& frame, int desktopWidth, int desktopHeight) {
        SDL_SetWindowPosition(window.get(), 
                            desktopWidth - frame.get_width(), 
                            desktopHeight - frame.get_height() - 150);
    }

    void DesktopPet::handle_menu_event(HWND hwnd, int desktopWidth, int desktopHeight) {
        int windowX, windowY, mouseX, mouseY;

        SDL_GetWindowPosition(window.get(), &windowX, &windowY);
        SDL_GetMouseState(&mouseX, &mouseY);

        PopupMenu menu;
        auto key = menu.wait_for_click(hwnd, windowX + mouseX, windowY + mouseY);

        switch(key) {
            case MENU_INDEX_CLOSE:
                running = false;
                break;
            case MENU_INDEX_CHANGE:
                animations.change_current_character(renderer.get());
                break;
            case MENU_INDEX_TOOLS:
            default:
                break;
        }
    }

    void DesktopPet::show() {
        HWND hwnd = get_underlying_window_handle();
        set_background_transparent(hwnd);

        const auto [desktopWidth, desktopHeight] = get_user_desktop_size();
        set_frame_position(animations.get_current().get_frame(0), desktopWidth, desktopHeight);

        int originalMouseX, originalMouseY, currentMouseX, currentMouseY, windowX, windowY;
        Uint32 startTime, endTime, frameTime;
        bool isDragging = false;
        SDL_Event event;

        while (running) {
            startTime = SDL_GetTicks();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_USEREVENT:
                        animations.render_current_character_frame(window.get(), renderer.get());
                        animations.update_current_character_frame();
                        
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (isDragging && event.button.button == SDL_BUTTON_LEFT) {
                            isDragging = false;
                        }

                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (!isDragging && event.button.button == SDL_BUTTON_LEFT) {
                            isDragging = true;
                            SDL_GetMouseState(&originalMouseX, &originalMouseY);
                        }
                        else if (event.button.button == SDL_BUTTON_RIGHT) {
                            isUserClickMenu = true;
                            handle_menu_event(hwnd, desktopWidth, desktopHeight);
                            isUserClickMenu = false;
                        }

                        break;
                    case SDL_MOUSEMOTION:
                        if (isDragging) {
                            SDL_GetWindowPosition(window.get(), &windowX, &windowY);
                            SDL_GetMouseState(&currentMouseX, &currentMouseY);
                            SDL_SetWindowPosition(window.get(), 
                                                windowX + (currentMouseX - originalMouseX), 
                                                windowY + (currentMouseY - originalMouseY));
                        }
                        
                        break;
                    default:
                        break;
                }
            }
            
            endTime = SDL_GetTicks();
            frameTime = endTime - startTime;

            if (frameTime < MAIN_FRAME_DELAY_MILLISEC) {
                SDL_Delay(MAIN_FRAME_DELAY_MILLISEC - frameTime);
            }
        }
    }
}
