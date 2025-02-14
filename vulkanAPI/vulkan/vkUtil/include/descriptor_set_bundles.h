#pragma once


#include "config.h"

#include "vkUtil\include\shader_bundles.h"

namespace vkUtil
{

	struct DescriptorSetBindingBundle
	{
		vk::DescriptorType type;
		vkUtil::ShaderStage stage;
		uint32_t count;  // number of descriptors
		uint32_t binding;
		vk::Sampler* sampler = nullptr;

	};


	struct DescriptorSetInBundle
	{
		std::vector<DescriptorSetBindingBundle> bindings;
	};

	struct DescriptorLayoutBundle
	{
		std::vector<uint32_t> descriptorCount;
		std::vector<vk::DescriptorType> descriptorType;
	};


	struct DescriptorSetOutBundle
	{
		std::vector<vk::DescriptorSet> descriptorSets;
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
		vk::DescriptorPool pool;
	};

}