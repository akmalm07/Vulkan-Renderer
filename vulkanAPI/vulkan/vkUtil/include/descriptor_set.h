#pragma once


#include "config.h"
#include "vkUtil\include\descriptor_set_bundles.h"


namespace vkUtil
{

	DescriptorSetOutBundle create_descriptor_set(const std::vector<DescriptorSetInBundle>& input); 
	 
	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& input);

	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& input);

	vk::DescriptorPool create_descriptor_pool(vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets);

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const vk::DescriptorSetLayout& layout, uint32_t descriptorSetCount);
	

	// ADD A REGISTERY class FOR DESCRIPTOR SETS LAYOUTS!!!!
}