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

    Pointer concat(List ls1, List ls2)
    {
        Pointer node(new Node);
        List* new_ls = new List();
        new_ls->insert(new_ls->end(), ls1.begin(), ls1.end());
        new_ls->insert(new_ls->end(), ls2.begin(), ls2.end());
        node->set_list(new_ls);
        return node;
    }
}