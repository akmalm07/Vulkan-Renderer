#pragma once

#include <cstdint>

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
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include <optional>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <type_traits>
#include <variant>
#include <memory>
#include <set>
#include <array>
#include <list>
#include <ranges>
#include <stack>
#include <chrono>
#include <thread>




#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 

#include "vkInit\include\predefines.h"

#include "vkInit\include\user_inputs.h"

#include "vkInit\include\debug.h"

#include "vkInit\include\types.h"