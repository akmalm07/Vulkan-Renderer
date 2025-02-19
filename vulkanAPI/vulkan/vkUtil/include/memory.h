#pragma once


#include "config.h"

#include "vkUtil\include\buffers.h" 



namespace vkUtil
{


	vk::Buffer create_buffer(const vk::Device& logicalDevice, BufferInput& input, bool debug);


	uint32_t find_memory_type_index(const vk::PhysicalDevice& physicalDevice, uint32_t supportedMemoryIndex, vk::MemoryPropertyFlags requestedProperties);


	vk::DeviceMemory alloc_buffer_memory(vk::Buffer& buffer, const vk::PhysicalDevice& device, const vk::Device& logicalDevice, BufferInput& input);


	void copy_buffer(vk::Buffer& srcBuffer, vk::Buffer& dstBuffer, vk::DeviceSize size, vk::CommandBuffer& commandBuffer);

	Buffer create_vk_util_buffer(const vk::PhysicalDevice& device, const vk::Device& logicalDevice, BufferInput& input, void* data, bool debug);


	void destroy_vk_util_buffer(const vk::Device& dev, Buffer buffer);

}


