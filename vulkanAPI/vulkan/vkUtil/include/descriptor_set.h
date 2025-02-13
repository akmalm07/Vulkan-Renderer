#pragma once


#include "config.h"
#include "vkUtil\include\descriptor_set_bundles.h"


namespace vkUtil
{

	DescriptorSetOutBundle create_descriptor_set(const std::vector<DescriptorSetInBundle>& input, std::vector<uint32_t> layouts, bool debug);
	 
	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& input, bool debug);

	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& input, bool debug);

	vk::DescriptorPool create_descriptor_pool(vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets, bool debug);

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const vk::DescriptorSetLayout& layout, uint32_t descriptorSetCount, bool debug);
	
	vk::DescriptorType to_descriptor_type(const std::string_view& type);

	// ADD A REGISTERY class FOR DESCRIPTOR SETS LAYOUTS!!!!
}