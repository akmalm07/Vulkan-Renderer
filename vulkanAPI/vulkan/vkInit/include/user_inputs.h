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

	constexpr char v_shader_path[] = "..\\shaders\\vertex.spv";
	constexpr char f_shader_path[] = "..\\shaders\\fragment.spv";
	constexpr char desc_set_json_path[] = "json\\descriptor_sets.json";
	constexpr char push_const_json_path[] = "json\\push_const.json";


	constexpr vk::ClearValue clear_color = { std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f} };


} // namespace UserInput