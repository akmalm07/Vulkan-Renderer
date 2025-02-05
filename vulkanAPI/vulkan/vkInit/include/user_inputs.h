#pragma once

#include <cstdint>

#include <glm/glm.hpp>
#include "predefines.h"


namespace UserInput
{
	//USER DEFITIONS
	using pos = glm::vec2;

	using col = glm::vec3;

	using norm = std::nullptr_t;

	using tex = std::nullptr_t;

	using AttributeDescription = AllInOneVertBuffer; 

	const char v_shader_path[] = "..\\shaders\\vertex.spv";
	const char f_shader_path[] = "..\\shaders\\fragment.spv";

	const vk::ClearValue clear_color = { std::array<float, 4>{1.0f, 0.0f, 1.0f, 1.0f} };



} // namespace UserInput