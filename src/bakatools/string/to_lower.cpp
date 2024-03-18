#include "string_tools.h"

namespace Bk::Tools {
    std::string string_to_lower(std::string& str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            str[i] = std::tolower(str[i]);
        }
        return str;
    }
}