#pragma once

#include <cstdint>

#include <glm/glm.hpp>
#include "predefines.h"


namespace UserInput
{

#define _POS_ glm::vec3

#define _COL_ glm::vec3

#define _NORM_ std::nullptr_t

#define _TEX_ std::nullptr_t

#define _VERT_SHADER_PATH_ "..\\shaders\\spv\\vertex.spv"

#define _FRAG_SHADER_PATH_ "..\\shaders\\spv\\fragment.spv"

#define LINE_VERT_SHADER_PATH_ "..\\shaders\\spv\\vertex_line.spv"

#define LINE_FRAG_SHADER_PATH_ "..\\shaders\\spv\\fragment_line.spv"


	//USER DEFITIONS
	using pos = _POS_;

	using col = _COL_;

	using norm = _NORM_;

	using tex = _TEX_;

	using AttributeDescription = AllInOneVertBuffer; // IF YOu Edit this, make nessasary changes to the Engine and Shaders

	constexpr char v_shader_path[] = _VERT_SHADER_PATH_;
	constexpr char f_shader_path[] = _FRAG_SHADER_PATH_;
	constexpr char line_v_shader_path[] = LINE_VERT_SHADER_PATH_;
	constexpr char line_f_shader_path[] = LINE_FRAG_SHADER_PATH_;
	constexpr char desc_set_json_path[] = "..\\json\\descriptor_sets.json";
	constexpr char push_const_json_path[] = "..\\json\\push_const.json";


	constexpr vk::ClearValue clear_color = { std::array<float, 4>{0.0f, 1.0f, 0.0f, 1.0f} };


} // namespace UserInput