#pragma once

#include "config.h"

namespace vkUtil
{
	enum class ShaderStage
	{
		VERTEX = vk::ShaderStageFlagBits::eVertex,
		FRAGMENT = vk::ShaderStageFlagBits::eFragment,
		COMPUTE = vk::ShaderStageFlagBits::eCompute
	};


	vk::ShaderStageFlagBits enum_to_vk(ShaderStage stage);

	ShaderStage to_shader_stage(const std::string_view& stage);

}
