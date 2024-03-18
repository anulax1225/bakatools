#include "string_tools.h"

namespace Bk::Tools {
    std::unique_ptr<std::vector<std::string>> string_split(std::string& str, std::string delimiter, int cpt)
    {
        std::string s(str);
        std::unique_ptr<std::vector<std::string>> splits(new std::vector<std::string>(0));
        size_t pos = 0;
        while (((pos = s.find(delimiter)) != std::string::npos) && cpt-- != 0) 
        {
            splits->push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        if (s.length()) splits->push_back(s);
        return splits;
    }
}