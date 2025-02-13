#pragma once


#include "config.h"

#include "vkUtil\include\shader_bundles.h"

namespace vkUtil
{

	struct DescriptorSetBindingBundle
	{
		vk::DescriptorType type;
		vkUtil::ShaderStage stage;
		uint32_t count;
		uint32_t binding;
		vk::Sampler* sampler = nullptr;

	};


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
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
		vk::DescriptorPool pool;
	};

}