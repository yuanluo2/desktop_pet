#pragma once

#include <Windows.h>
#include <string>

/**
 * These functions are only used for windows platform.
*/
namespace desktop_pet {
    std::wstring conv_ascii_to_unicode(const std::string& str);
    std::string conv_unicode_to_ascii(const std::wstring& wstr);
    std::wstring conv_utf8_to_unicode(const std::string& str);
    std::string conv_utf8_to_ascii(const std::string& str);
    std::string conv_unicode_to_utf8(const std::wstring& wstr);
}
