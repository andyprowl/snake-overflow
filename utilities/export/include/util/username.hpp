#pragma once

#include "util/string_conversion.hpp"
#include <lmcons.h>

namespace util
{
    
inline std::string get_current_username()
{
    auto length = static_cast<unsigned long>(UNLEN + 1);

    wchar_t username[UNLEN + 1];
    
    GetUserName(username, &length); 

    return to_string(username);
}

}