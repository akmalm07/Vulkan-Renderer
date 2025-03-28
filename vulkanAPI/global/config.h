#pragma once

#include <cstdint>

#include <vulkan\vulkan.hpp>

#include <GLFW\glfw3.h>																				

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\quaternion.hpp>


#include "vkInit\include\predefines.h"

#include "vkInit\include\user_inputs.h"

#include "vkInit\include\debug.h"

#include "vkInit\include\types.h"


#if KEY_MAX < 2
#error "KEY_MAX CANNOT BE LESS THEN 2!!" 
#endif






