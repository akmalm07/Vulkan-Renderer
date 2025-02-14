#pragma once


#include "config.h"
#include "vkUtil\include\descriptor_set_bundles.h"


namespace vkUtil
{

	DescriptorSetOutBundle create_descriptor_set(const vk::Device& device, const std::vector<DescriptorSetInBundle>& input, std::vector<DescriptorLayoutBundle> layouts, bool debug);
	 
	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& input, bool debug);

	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& input, bool debug);

	vk::DescriptorPool create_descriptor_pool(const vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets, bool debug);

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const std::vector<vk::DescriptorSetLayout>& layout, uint32_t descriptorSetCount, bool debug);
	
	vk::DescriptorType to_descriptor_type(const std::string_view& type);
	
	//Helper Functions

	bool already_exists(const vk::DescriptorSetLayoutCreateInfo& check, const DescriptorLayoutBundle& toCheck);
}