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

#define BOOL(x) static_cast<bool>(x)

#define PRINT_VEC3(str, v) std::cout << str << ": " << v.x << " " << v.y << " " << v.z << std::endl;

#define PRINT_MAT4(str, v) std::cout << str << ": \n" << v[0][0] << " " << v[0][1] << " " << v[0][2] << " " << v[0][3] << std::endl; \
std::cout << v[1][0] << " " << v[1][1] << " " << v[1][2] << " " << v[1][3] << std::endl; \
std::cout << v[2][0] << " " << v[2][1] << " " << v[2][2] << " " << v[2][3] << std::endl; \
std::cout << v[3][0] << " " << v[3][1] << " " << v[3][2] << " " << v[3][3] << std::endl;

#define UINT(x) static_cast<unsigned int>(x)

#define INT(x) static_cast<int>(x)

using OncePerVertBuffer = vk::VertexInputAttributeDescription; 
using AllInOneVertBuffer = std::vector<vk::VertexInputAttributeDescription>; 

