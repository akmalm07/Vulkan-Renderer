#pragma once

#include <string>
#include <iostream>

#define UINT32(x) static_cast<uint32_t>(x)

#define SIZET(x) static_cast<size_t>(x)

#define ASSERT(cond, msg) if (!(cond)) { std::cerr << msg << std::endl; } 

#define INDEX_TYPE uint16_t 