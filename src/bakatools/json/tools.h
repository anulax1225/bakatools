#pragma once

#include <bakatoolspch.h>
#include "node.h"

namespace Bk::Json 
{
    Pointer find_key(std::string name, Object obj);
    bool as_key(std::string name, Object obj);
    Pointer concat(List ls1, List ls2);
}