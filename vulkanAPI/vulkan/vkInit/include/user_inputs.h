#pragma once

#include <cstdint>

#include <glm/glm.hpp>
#include "predefines.h"


namespace UserInput
{
	//USER DEFITIONS
	using pos = glm::vec3;

	using col = glm::vec3;

	using norm = std::nullptr_t;

	using tex = std::nullptr_t;

	using AttributeDescription = AllInOneVertBuffer; 

	const char v_shader_path[] = "..\\shaders\\vertex.spv";
	const char f_shader_path[] = "..\\shaders\\fragment.spv";
	const char desc_set_json_path[] = "json\\descriptor_sets.json";
	const char push_const_json_path[] = "json\\push_const.json";


	const vk::ClearValue clear_color = { std::array<float, 4>{1.0f, 5.0f, 0.0f, 0.3f} };


} // namespace UserInput