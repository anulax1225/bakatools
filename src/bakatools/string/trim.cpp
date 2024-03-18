#include "string_tools.h"

namespace Bk::Tools {
    void string_trim(std::string& str, const std::string& whitespace)
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        const auto strEnd = str.find_last_not_of(whitespace);
        if (strBegin != std::string::npos)
        {
            str.erase(0, strBegin);
        }
    }
}