#pragma once

#include <bakatools.h>
#include "format.h"

namespace Bk::Tools {
    std::string string_to_lower(std::string& str);
    std::string string_to_upper(std::string& str);
    std::unique_ptr<std::vector<std::string>> string_split(std::string& str, std::string delimiter, int cpt = -1);
    void string_trim(std::string& str, const std::string& whitespace = " \b\0");
}