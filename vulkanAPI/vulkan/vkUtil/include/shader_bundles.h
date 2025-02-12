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


}
