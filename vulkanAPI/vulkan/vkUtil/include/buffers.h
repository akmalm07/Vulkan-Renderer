#pragma once

#include "config.h"


namespace vkUtil {

	class Buffer
	{
	public:

		vk::Buffer buffer;
		vk::DeviceMemory bufferMemory;
	};



	struct BufferInput
	{
	public:
		vk::Device logicalDevice;
		vk::PhysicalDevice device;
		size_t size;
		vk::BufferUsageFlags usage;

	};

}


namespace vkMesh {

	struct BufferInitInput
	{
		vk::Device logicalDevice;
		vk::PhysicalDevice physicalDevice;
	};

}
