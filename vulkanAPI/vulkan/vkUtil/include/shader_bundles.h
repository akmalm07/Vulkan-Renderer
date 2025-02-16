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

	vk::ShaderStageFlags mix_shader_flags_of_vector(const std::vector<vkUtil::ShaderStage>& flags);

	std::vector<vk::ShaderStageFlagBits> to_vk_shader_flags(const std::vector<ShaderStage>& flags);

}
