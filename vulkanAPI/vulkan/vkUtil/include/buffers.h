#pragma once

#include "pch.h"


namespace vkUtil {

	class Buffer //Father of Index and Vertex Buffer Classes
	{
	public:

		vk::Buffer buffer;
		vk::DeviceMemory bufferMemory;
	protected:
	};


	struct BufferInput
	{

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
