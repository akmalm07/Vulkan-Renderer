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

	vk::ShaderStageFlags mix_shader_flags_of_vector(const std::vector<ShaderStage>& flags)
	{
		if (flags.empty())
		{
			return vk::ShaderStageFlags();
		}

		std::vector<vk::ShaderStageFlagBits> output = to_vk_shader_flags(flags);


		vk::ShaderStageFlags theoutput;
		for (const auto& flag : output)
		{
			theoutput |= flag;
		}
		return theoutput;
	}

	std::vector<vk::ShaderStageFlagBits> to_vk_shader_flags(const std::vector<ShaderStage>& flags)
	{
		std::vector<vk::ShaderStageFlagBits> output(flags.size());
		for (const auto& [i, flag] : flags | std::views::enumerate)
		{
			output[i] = enum_to_vk(flag);
		}
		return output;
	}

}