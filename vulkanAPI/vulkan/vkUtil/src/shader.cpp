#include "pch.h"

#include "shader.h"

namespace vkInit
{

	std::vector<char> read_file(std::filesystem::path& path, bool debug)
	{
		if (!std::filesystem::exists(path))
		{
			std::cerr << "Error: entered invalid path name for \"" << path << "\" \n";
			return {};
		}

		std::ifstream fileInput(path, std::ios::ate | std::ios::binary);

		if (!fileInput.is_open())
		{
			std::cerr << "Error: could not open the following file: \"" << path << "\"" << std::endl;
		}

		size_t fileSize{ static_cast<size_t>(fileInput.tellg()) };


		std::vector<char> buffer(fileSize);

		fileInput.seekg(0);

		fileInput.read(buffer.data(), fileSize);

		fileInput.close();

		return buffer;
	}

	vk::ShaderModule create_shader_module(std::filesystem::path& path, vk::Device logicalDevice, bool debug)
	{

		if (debug)
		{
			std::cout << "Creating shader module...\n";
		}

		std::vector sourceCode = read_file(path, debug);

		vk::ShaderModuleCreateInfo createInfo = {};

		createInfo.flags = vk::ShaderModuleCreateFlags();
		createInfo.codeSize = sourceCode.size();
		createInfo.pCode = reinterpret_cast<uint32_t*>(sourceCode.data());

		try
		{
			return logicalDevice.createShaderModule(createInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "Error creating Shader module: " << err.what() << "\n";
			return nullptr;
		}


		return nullptr;
	}
}