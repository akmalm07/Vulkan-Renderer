#include "memory.h"



vk::Buffer vkUtil::create_buffer(BufferInput& input, bool debug)
{

	vk::BufferCreateInfo bufferInfo = {};

	bufferInfo.flags = vk::BufferCreateFlags();

	bufferInfo.size = input.size;

	bufferInfo.usage = input.usage;

	bufferInfo.sharingMode = vk::SharingMode::eExclusive;

	vk::Buffer buffer; 
	try
	{
		buffer = input.logicalDevice.createBuffer(bufferInfo); 
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

uint32_t vkUtil::find_memory_type_index(vk::PhysicalDevice& physicalDevice, uint32_t supportedMemoryIndex, vk::MemoryPropertyFlags requestedProperties)
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


vk::DeviceMemory vkUtil::alloc_buffer_memory(vk::Buffer& buffer, BufferInput& input)
{

	vk::MemoryRequirements memReq = input.logicalDevice.getBufferMemoryRequirements(buffer);

	vk::MemoryAllocateInfo allocInfo = {};

	vk::DeviceMemory bufferMemory = {};

	if (memReq.size == 0)
	{
		std::cout << "\n\nError! Alloaction size cannot be 0, must be greater then 0\n";
		throw std::runtime_error("Allocation size set to 0");
	}

	allocInfo.allocationSize = memReq.size;

	allocInfo.memoryTypeIndex = vkUtil::find_memory_type_index( 
		input.device,
		memReq.memoryTypeBits,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
	);

	try
	{
		bufferMemory = input.logicalDevice.allocateMemory(allocInfo);
	}
	catch (vk::SystemError& err)
	{
		std::cout << "Error allocating buffer memory! Error Message: " << err.what() << "\n";
	}

	try
	{
		input.logicalDevice.bindBufferMemory(buffer, bufferMemory, 0);
	}
	catch (vk::SystemError& err)
	{
		std::cout << "Error binding the buffer memory! Error Message: " << err.what() << "\n";
	}

	return bufferMemory;
}
