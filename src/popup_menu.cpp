#include "popup_menu.h"
#include "encoding.h"
#include "constant.h"
#include <string>

namespace desktop_pet {
    PopupMenu::PopupMenu() {
        menu = CreatePopupMenu();

        std::string close = conv_utf8_to_ascii("关闭");
        std::string change = conv_utf8_to_ascii("切换动作");
        std::string tools = conv_utf8_to_ascii("工具");

        AppendMenuA(menu, MF_STRING, MENU_INDEX_CLOSE, close.c_str());
        AppendMenuA(menu, MF_STRING, MENU_INDEX_CHANGE, change.c_str());
        AppendMenuA(menu, MF_STRING, MENU_INDEX_TOOLS, tools.c_str());
    }

    PopupMenu::~PopupMenu() noexcept {
        if (menu != nullptr) {
            DestroyMenu(menu);
        }
    }

    WINBOOL PopupMenu::wait_for_click(HWND parent, int x, int y) {
        return TrackPopupMenuEx(menu, TPM_RETURNCMD, x, y, parent, nullptr);
    }
}