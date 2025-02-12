#pragma once


#include "config.h"

#include "vkUtil\include\shader_bundles.h"

namespace vkUtil
{

	struct DescriptorSetInBundle
	{
		static vk::Device& device;
		std::vector<DescriptorSetBindingBundle> bindings;
		uint32_t descriptorSetCount;
		uint32_t poolNumber;
	};


	struct DescriptorSetOutBundle
	{
		std::vector<vk::DescriptorSet> descriptorSets;
		vk::DescriptorPool pool;
	};


	struct DescriptorSetBindingBundle
	{
		vk::Device& device;
		vk::DescriptorType type;
		vkUtil::ShaderStage stage;
		uint32_t count;
		uint32_t binding;
		vk::Sampler* sampler = nullptr;
	};
}