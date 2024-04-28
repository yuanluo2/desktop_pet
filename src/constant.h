#pragma once

/**
 * The constants used in this program.
*/
namespace desktop_pet {
    inline constexpr auto PET_FRAME_UPDATE_RATE = 10;
    inline constexpr auto PET_FRAME_UPDATE_MILLISEC = 1000 / PET_FRAME_UPDATE_RATE;
    
    inline constexpr auto MAIN_FRAME_RATE = 60;
    inline constexpr auto MAIN_FRAME_DELAY_MILLISEC = 1000 / MAIN_FRAME_RATE;

    inline constexpr auto MENU_INDEX_CLOSE = 1;
    inline constexpr auto MENU_INDEX_CHANGE = 2;
    inline constexpr auto MENU_INDEX_TOOLS = 3;
}
