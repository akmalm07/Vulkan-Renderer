#pragma once


#include "config.h"

#include "vkUtil\include\buffers.h" 



namespace vkUtil 
{


	vk::Buffer create_buffer(BufferInput& input, bool debug);


	uint32_t find_memory_type_index(vk::PhysicalDevice& physicalDevice, uint32_t supportedMemoryIndex, vk::MemoryPropertyFlags requestedProperties);


	vk::DeviceMemory alloc_buffer_memory(vk::Buffer& buffer, BufferInput& input);


	void copy_buffer(vk::Buffer& srcBuffer, vk::Buffer& dstBuffer, vk::DeviceSize size, vk::CommandBuffer& commandBuffer);

	template<class T>
	Buffer create_vk_util_buffer(BufferInput& input, T& data, bool debug);

	template<vkType::IsArrOrVec T>
	Buffer create_vk_util_buffer(BufferInput& input, T& data, bool debug);

	void destroy_vk_util_buffer(const vk::Device& dev, Buffer buffer);






	template<class T>
	inline Buffer create_vk_util_buffer(BufferInput& input, T& data, bool debug)
	{

		vk::Buffer buff = create_buffer(input, debug);
		vk::DeviceMemory mem = alloc_buffer_memory(buff, input);

		void* memLocation = input.logicalDevice.mapMemory(mem, 0, input.size);

		if (!memLocation)
		{
			throw std::runtime_error("Failed to map memory!");
		}

		memcpy(memLocation, &data, input.size);

		input.logicalDevice.unmapMemory(mem);


		return { buff, mem };

	}

	template<vkType::IsArrOrVec T>
	inline Buffer create_vk_util_buffer(BufferInput& input, T& data, bool debug)
	{

		vk::Buffer buff = create_buffer(input, debug);
		vk::DeviceMemory mem = alloc_buffer_memory(buff, input);

		void* memLocation = input.logicalDevice.mapMemory(mem, 0, input.size);

		if (!memLocation)
		{
			throw std::runtime_error("Failed to map memory!");
		}

		memcpy(memLocation, data.data(), input.size);

		input.logicalDevice.unmapMemory(mem);


		return { buff, mem };

	}
}