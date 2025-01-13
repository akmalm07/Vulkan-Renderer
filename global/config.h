#pragma once


//statically load vulkan library
#include <vulkan\vulkan.hpp>
/*
* Statically linking the prebuilt header from the lunarg sdk will load
* most functions, but not all.
*
* Functions can also be dynamically loaded, using the call
*
* PFN_vkVoidFunction vkGetInstanceProcAddr(
	VkInstance                                  instance,
	const char*                                 pName);

 or

 PFN_vkVoidFunction vkGetDeviceProcAddr(
	VkDevice                                    device,
	const char*                                 pName);

	We will look at this later, once we've created an instance and device.
*/

#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <memory>
#include <type_traits>
#include <variant>
#include <memory>


#include <cstdint>


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 



using INDEX_TYPE = uint16_t;

template <class T>
inline uint32_t cast_uint32(T val)
{
	return static_cast<uint32_t>(val);
}

namespace vkUtil {


}
