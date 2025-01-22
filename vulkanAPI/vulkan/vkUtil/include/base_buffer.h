#pragma once

#include "config.h"

#include "vkUtil\include\buffers.h"

#include "vkUtil\include\memory.h"



class BufferFather //Father of Index and Vertex Buffer Classes
{
public:
	BufferFather();

	explicit BufferFather(const vkUtil::BufferInitInput& input);

	void clean_buffer();

	vk::Buffer get_buffer() const;


	virtual ~BufferFather();
protected:

	vk::Buffer buffer;
	vk::DeviceMemory bufferMemory;

	vk::Device device;
	vk::PhysicalDevice physicalDevice;


	template <vkType::BufferType T>
	void createBuffer(std::vector<T>& data, vk::DeviceMemory& bufferMemory, vk::BufferUsageFlagBits usage, size_t& count, bool debug)
	{
		std::string_view bufferStr = (usage == vk::BufferUsageFlagBits::eVertexBuffer ? "vertex" : (usage == vk::BufferUsageFlagBits::eIndexBuffer ? "index" : "unknown buffer"));

			if (debug)
			{
				std::cout << "Initalizing the " << bufferStr << " buffer...\n";

				if (data.empty())
				{
					std::cout << "Error! The vector inserted into the initialize function of " << bufferStr << " Buffer is empty\n";
				}
			}



		vkUtil::BufferInput input = {};
		input.device = physicalDevice;
		input.logicalDevice = device;
		input.size = data.size() * sizeof(data[0]);
		input.usage = usage;


		buffer = vkUtil::create_buffer(input, debug);
		if (debug)
		{
			std::cout << "Creating the " << bufferStr << " buffer...\n";
			if (!buffer)
			{
				std::cout << "Error: Failed to create " << bufferStr << " buffer!\n";
			}
		}


		bufferMemory = vkUtil::alloc_buffer_memory(buffer, input);
		if (debug)
		{
			std::cout << "Allocating the " << bufferStr << " buffer...\n";

			if (!bufferMemory)
			{
				std::cout << "Error: Failed to allocate " << bufferStr << " buffer memory!\n";
			}
		}


		void* memLocation = device.mapMemory(bufferMemory, 0, input.size);

		if (!memLocation)
		{
			std::cout << "Error: Failed to map memory!\n";
		}

		memcpy(memLocation, data.data(), input.size);

		device.unmapMemory(bufferMemory);


		count = data.size();
	}
};