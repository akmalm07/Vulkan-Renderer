#include "pch.h"

#include "base_buffer.h"

#include "vkUtil\include\buffers.h"




BufferFather::BufferFather() : device(nullptr), physicalDevice(nullptr), buffer(nullptr), bufferMemory(nullptr)
{
}


BufferFather::BufferFather(const vkUtil::BufferInitInput& input)
	: device(input.logicalDevice), physicalDevice(input.physicalDevice)
{
}


void BufferFather::clean_buffer()
{
	if (buffer)
	{
		device.destroyBuffer(buffer);
		buffer = nullptr;
	}
	if (bufferMemory)
	{
		device.freeMemory(bufferMemory);
		bufferMemory = nullptr;
	}
	device = nullptr;
	physicalDevice = nullptr;
}


vk::Buffer BufferFather::get_buffer() const
{
	return buffer;
}


BufferFather::~BufferFather()
{
	clean_buffer();
}