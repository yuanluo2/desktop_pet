#include "encoding.h"
#include <cstdint>
#include <stdexcept>
#include <system_error>

namespace desktop_pet {
    static std::error_code get_last_sys_ec(){
        return std::error_code(GetLastError(), std::system_category());
    }

    static void throw_last_sys_error(const std::string& msg) {
        auto ec = get_last_sys_ec();
        throw std::runtime_error{ msg + ", error detail: " + ec.message() };
    }

    std::wstring conv_ascii_to_unicode(const std::string& str) {
        auto len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
        if (len == 0) {
            throw_last_sys_error("conv_ascii_to_unicode() failed");
        }

        std::wstring buffer(len, wchar_t{});
        len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &buffer[0], len);
        if (len == 0) {
            throw_last_sys_error("conv_ascii_to_unicode() failed");
        }

        /*
        * a very tricky thing here is, if the underlying string stored in fs::path <p> ends with '\0',
        * when you pass the <p> to the fs::directory_iterator, you would get a file not found exception.
        * but if I pass <p.c_str()> to the fs::directory_iterator, then that will work as expected. I tested it on
        * the visual studio and clang++, and both represent this bug, but '\0' doesn't influence the functions like
        * fs::is_directory or fs::is_regular_file, so this is really interesting.
        *
        * This function and the functions below are all doing the encoding conversion,
        * and all of the <len> used in the functions contains '\0', to prevent the tricky behaviour like fs::directory_iterator,
        * we resize the buffer to ignore the tail '\0'.
        */
        buffer.resize(len - 1);
        return buffer;
    }

    std::string conv_unicode_to_ascii(const std::wstring& wstr) {
        auto len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (len == 0) {
            throw_last_sys_error("conv_unicode_to_ascii() failed");
        }

        std::string buffer(len, char{});

        if (WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &buffer[0], len, nullptr, nullptr) == 0) {
            throw_last_sys_error("conv_unicode_to_ascii() failed");
        }

        buffer.resize(len - 1);   // same reason as std::wstring conv_ascii_to_unicode(const std::string& str);
        return buffer;
    }

    std::wstring conv_utf8_to_unicode(const std::string& str) {
        auto len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        if (len == 0) {
            throw_last_sys_error("conv_utf8_to_unicode() failed");
        }

        std::wstring buffer(len, wchar_t{});
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], len - 1);
        if (len == 0) {
            throw_last_sys_error("conv_utf8_to_unicode() failed");
        }

        buffer.resize(len - 1);   // same reason as std::wstring conv_ascii_to_unicode(const std::string& str);
        return buffer;
    }

    std::string conv_utf8_to_ascii(const std::string& str) {
        std::wstring wstr = conv_utf8_to_unicode(str);
        return conv_unicode_to_ascii(wstr);
    }

    std::string conv_unicode_to_utf8(const std::wstring& wstr) {
        std::string result;

        for (wchar_t c : wstr) {
            auto i = static_cast<uint32_t>(c);   // as you can see, the parameter could also be u32string.

            if (i < 0x80) {
                result += static_cast<char>(i);
            }
            else if (i < 0x800) {
                result += static_cast<char>(0xc0 | (i >> 6));
                result += static_cast<char>(0x80 | (i & 0x3f));
            }
            else if (i < 0x10000) {
                result += static_cast<char>(0xe0 | (i >> 12));
                result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
                result += static_cast<char>(0x80 | (i & 0x3f));
            }
            else if (i < 0x200000) {
                result += static_cast<char>(0xf0 | (i >> 18));
                result += static_cast<char>(0x80 | ((i >> 12) & 0x3f));
                result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
                result += static_cast<char>(0x80 | (i & 0x3f));
            }
            else {
                result += static_cast<char>(0xf8 | (i >> 24));
                result += static_cast<char>(0x80 | ((i >> 18) & 0x3f));
                result += static_cast<char>(0x80 | ((i >> 12) & 0x3f));
                result += static_cast<char>(0x80 | ((i >> 6) & 0x3f));
                result += static_cast<char>(0x80 | (i & 0x3f));
            }
        }

        return result;
    }
}