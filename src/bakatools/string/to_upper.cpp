#include "string_tools.h"

namespace Bk::Tools {
    std::string string_to_upper(std::string& str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            str[i] = std::toupper(str[i]);
        }
        return str;
    }
}