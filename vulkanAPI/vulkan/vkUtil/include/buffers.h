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
		size_t size;
		vk::BufferUsageFlags usage;

	};


	struct BufferInitInput
	{
		vk::Device logicalDevice;
		vk::PhysicalDevice physicalDevice;
	};
}