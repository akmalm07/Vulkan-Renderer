#include "pch.h"

#include "vkUtil\include\shader_bundles.h"


namespace vkUtil
{

	vk::ShaderStageFlagBits enum_to_vk(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::VERTEX:
			return vk::ShaderStageFlagBits::eVertex;
		case ShaderStage::FRAGMENT:
			return vk::ShaderStageFlagBits::eFragment;
		case ShaderStage::COMPUTE:
			return vk::ShaderStageFlagBits::eCompute;
		default:
			return vk::ShaderStageFlagBits();
		}
	}

	ShaderStage to_shader_stage(const std::string_view& stage)
	{
		if (stage == "vertex")
		{
			return ShaderStage::VERTEX;
		}
		else if (stage == "fragment")
		{
			return ShaderStage::FRAGMENT;
		}
		else if (stage == "compute")
		{
			return ShaderStage::COMPUTE;
		}
		else
		{
			throw std::runtime_error("Shader Stage not found");
		}
	}


}