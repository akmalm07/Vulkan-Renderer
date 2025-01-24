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

}



namespace vkInit {

	std::vector<char> read_file(std::filesystem::path& path, bool debug);
	vk::ShaderModule create_shader_module(std::filesystem::path& path, vk::Device logicalDevice, bool debug);

}
