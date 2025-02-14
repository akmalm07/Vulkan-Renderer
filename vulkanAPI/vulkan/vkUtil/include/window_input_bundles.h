#pragma once

#include "tools\include\keys.h"

namespace vkUtil
{
    struct KeyCombInput
    {
        Keys number; 
        Action action; 
        Mods mod = Mods::None;
    };

    struct MouseButtonInput
    {
        Mouse name;
        Action action;
    };

    struct AABButtonInput
    {
        float cordX, cordY, width, height;
        Action action;
        Mouse button;
        std::string_view name;
    };
}