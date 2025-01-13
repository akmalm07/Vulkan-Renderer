
#pragma once


#include "config.h"

#include "buffers.h" 



namespace vkUtil {



	vk::Buffer create_buffer(BufferInput& input, bool debug);


	uint32_t find_memory_type_index(vk::PhysicalDevice& physicalDevice, uint32_t supportedMemoryIndex, vk::MemoryPropertyFlags requestedProperties);


	vk::DeviceMemory alloc_buffer_memory(vk::Buffer& buffer, BufferInput& input);


}
