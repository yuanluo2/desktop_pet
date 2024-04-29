#include "init_img.h"
#include <string>
#include <stdexcept>

using namespace std::string_literals;

namespace desktop_pet {
    InitIMG::InitIMG(int flags) {
        if ((IMG_Init(flags) & flags) != flags) {
            throw std::runtime_error{ "IMG_Init() failed: "s + IMG_GetError() };
        }
    }

    InitIMG::~InitIMG() noexcept {
        IMG_Quit();
    }
}