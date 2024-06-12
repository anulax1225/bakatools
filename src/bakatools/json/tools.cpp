#include "tools.h"

namespace Bk::Json 
{
    Pointer find_key(std::string name, Object obj)
    {
        Pointer node(new Node());
        if (obj.find(name) != obj.end()) node = obj[name];
        else node->set_null();
        return node;
    }

    bool as_key(std::string name, Object obj)
    {
        return obj.find(name) != obj.end();
    }
}