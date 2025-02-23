#pragma once

#include <cstdint>

#include <vector> 
#include <iostream> 

namespace vk
{
	struct VertexInputAttributeDescription;

}

#define UINT32(x) static_cast<uint32_t>(x)  

#define SIZET(x) static_cast<size_t>(x) 

#define ASSERT(cond, msg) if (!(cond)) { std::cerr << msg << std::endl; } 

#define INDEX_TYPE uint16_t  

#define VERTEX_TYPE float 

#define SEND_REF(x) x

#define PRES_TY(x) std::forward<decltype(x)>(x) 

#define MOVE_ITR(x) std::make_move_iterator(x)

#define KEY_MAX 2 // CANNOT BE LESS THEN 2!!

#define PRINT_VEC3(str, v) std::cout << str << ": " << v.x << " " << v.y << " " << v.z << std::endl;

#define UINT(x) static_cast<unsigned int>(x)

#define INT(x) static_cast<int>(x)

using OncePerVertBuffer = vk::VertexInputAttributeDescription; 
using AllInOneVertBuffer = std::vector<vk::VertexInputAttributeDescription>; 