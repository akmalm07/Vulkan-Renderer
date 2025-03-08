#pragma once


#include "config.h"
#include "vkInit\include\descriptor_set_bundles.h"
#include "tools\include\memory_pool_container.h"


namespace vkInit
{

	DescriptorSetOutBundle create_descriptor_set(const vk::Device& device, const vk::PhysicalDevice& logicalDevice, 
		const std::vector<DescriptorSetBindings>& discriptor,
		const std::vector<DescriptorSetBindings>& layouts,
		std::vector<vkInit::DescriptorBuffer> buffers, bool debug);
	 
	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& input, bool debug);

	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& input, bool debug);

	vk::DescriptorPool create_descriptor_pool(const vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets, bool debug);

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const std::vector<vk::DescriptorSetLayout>& layout, uint32_t descriptorSetCount, bool debug);
	
	vk::DescriptorType to_descriptor_type(const std::string_view& type);
	
	vk::BufferUsageFlags to_buffer_type(const std::string_view& type);
	
	//Helper Functions

	bool already_exists(const vk::DescriptorSetLayoutCreateInfo& check, const vk::DescriptorSetLayoutCreateInfo& toCheck);
}