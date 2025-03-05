#include "headers.h"

#include "vkUtil\include\memory.h"
#include "vkUtil\include\buffers.h"


namespace vkUtil
{



	vk::Buffer create_buffer(const vk::Device& logicalDevice, BufferInput& input, bool debug)
	{

		vk::BufferCreateInfo bufferInfo = {};

		bufferInfo.flags = vk::BufferCreateFlags();

		bufferInfo.size = input.size;

		bufferInfo.usage = input.usage;

		bufferInfo.sharingMode = vk::SharingMode::eExclusive;

		vk::Buffer buffer;
		try
		{
			buffer = logicalDevice.createBuffer(bufferInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cout << "Error creating buffer! Error Message: " << err.what() << "\n";
		}

		if (!buffer)
		{
			std::cout << "\nError! Buffer is null\n";
		}

		return buffer;


	}

	uint32_t find_memory_type_index(const vk::PhysicalDevice& physicalDevice, uint32_t supportedMemoryIndex, vk::MemoryPropertyFlags requestedProperties)
	{

		vk::PhysicalDeviceMemoryProperties memProperties = physicalDevice.getMemoryProperties();

		for (size_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			bool supported = (supportedMemoryIndex & (1 << i));

			bool sufficient = ((memProperties.memoryTypes[i].propertyFlags & requestedProperties) == requestedProperties);

			if (supported && sufficient)
			{
				return i;
			}

		}

	}


	vk::DeviceMemory alloc_buffer_memory(vk::Buffer& buffer, const vk::PhysicalDevice& device, const vk::Device& logicalDevice, vkUtil::BufferInput& input)
	{

		vk::MemoryRequirements memReq = logicalDevice.getBufferMemoryRequirements(buffer);

		vk::MemoryAllocateInfo allocInfo = {};

		vk::DeviceMemory bufferMemory = {};

		if (memReq.size == 0)
		{
			throw std::runtime_error("Allocation size set to 0");
		}

		allocInfo.allocationSize = memReq.size;

		allocInfo.memoryTypeIndex = find_memory_type_index(
			device,
			memReq.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
		);

		try
		{
			bufferMemory = logicalDevice.allocateMemory(allocInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cout << "Error allocating buffer memory! Error Message: " << err.what() << "\n";
		}

		try
		{
			logicalDevice.bindBufferMemory(buffer, bufferMemory, 0);
		}
		catch (vk::SystemError& err)
		{
			std::cout << "Error binding the buffer memory! Error Message: " << err.what() << "\n";
		}

		return bufferMemory;
	}


	void copy_buffer(vk::Buffer& srcBuffer, vk::Buffer& dstBuffer, vk::DeviceSize size, vk::CommandBuffer& commandBuffer)
	{
		vk::BufferCopy copyRegion = {};
		copyRegion.size = size;
		commandBuffer.copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);
	}


	Buffer create_vk_util_buffer(const vk::PhysicalDevice& device, const vk::Device& logicalDevice, BufferInput& input, void* data, bool debug)
	{
		if (debug)
		{
			std::cout << "Creating Descriptor Buffer with size: " << input.size << " with usage: " << vk::to_string(input.usage) << std::endl;
		}

		vk::Buffer buff = create_buffer(logicalDevice, input, debug);
		vk::DeviceMemory mem = alloc_buffer_memory(buff, device, logicalDevice, input);

		void* memLocation = logicalDevice.mapMemory(mem, 0, input.size);

		if (!memLocation)
		{
			throw std::runtime_error("Failed to map memory!");
		}

		if (!data)
		{
			throw std::runtime_error("Data is null!");
		}
		memcpy(memLocation, data, input.size);

		logicalDevice.unmapMemory(mem);


		return { buff, mem };

	}




	void destroy_vk_util_buffer(const vk::Device& dev, Buffer buffer)
	{
		dev.freeMemory(buffer.bufferMemory);
		dev.destroyBuffer(buffer.buffer);
	}

}