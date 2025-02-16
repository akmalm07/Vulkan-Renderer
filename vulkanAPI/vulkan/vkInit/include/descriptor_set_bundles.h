#pragma once


#include "config.h"

#include "vkUtil\include\shader_bundles.h"

namespace vkInit
{

	struct DescriptorSetBindingBundle
	{
		vk::DescriptorType type;
		std::vector<vkUtil::ShaderStage> stage;
		uint32_t count;  // number of descriptors
		uint32_t binding;
		vk::Sampler* sampler = nullptr;

		DescriptorSetBindingBundle();

		DescriptorSetBindingBundle(vk::DescriptorType type, std::vector<vkUtil::ShaderStage> stage, uint32_t count, uint32_t binding, vk::Sampler* sampler = nullptr);

		DescriptorSetBindingBundle(vk::DescriptorType type, vkUtil::ShaderStage stage, uint32_t count, uint32_t binding, vk::Sampler* sampler = nullptr);
	};



	struct DescriptorSetOutBundle
	{
		std::vector<vk::DescriptorSet> descriptorSets;
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
		vk::DescriptorPool pool;
	};

}