#pragma once

#include "config.h"
/*

	- USE glm::vecX, x being from 2 to 4, for the stride positions
	- They will always be in this order:
		 POSITION 
		 COLOR 
		 NORMAL 
		 TEXTURE
	- If you don't desire one of the strides, use std::nullptr_t for it
	- Example:

		 

*/


using POSITION   =      glm::vec2;
using COLOR      =      glm::vec3; 
using NORMAL     =      std::nullptr_t; 
using TEXTURE    =      std::nullptr_t; 
