#pragma once

#include "config.h"



namespace vkInit 
{

	std::vector<char> read_file(std::filesystem::path& path, bool debug);
	vk::ShaderModule create_shader_module(std::filesystem::path& path, vk::Device logicalDevice, bool debug);

}
