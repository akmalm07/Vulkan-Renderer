#include "headers.h"

#include "vkUtil\include\command.h" 

vk::CommandPool vkInit::make_command_pool(vk::Device& logicalDevice, vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug)
{
	if (debug)
	{
		std::cout << "Creating command pool... \n";
	}
	vkUtil::QueueFamilyIndices queueFamily = vkUtil::find_queue_families(device, surface, debug); 
	
	vk::CommandPoolCreateInfo info = {};

	info.flags = vk::CommandPoolCreateFlags() | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;

	info.queueFamilyIndex = queueFamily.graphicsFamily.value();

	try
	{
		return logicalDevice.createCommandPool(info);
	}
	catch (vk::SystemError& err)
	{
		std::cout << "Error creating command pool: " << err.what() << "\n";
		return nullptr;
	}

	return nullptr;


}



vk::CommandBuffer vkInit::make_command_buffer(CommandBufferInput input, bool debug)
{
	vk::CommandBufferAllocateInfo allocationInfo = {};

	allocationInfo.commandPool = input.commandPool;

	allocationInfo.level = vk::CommandBufferLevel::ePrimary;

	allocationInfo.commandBufferCount = 1;

	try
	{
		vk::CommandBuffer commandBuffer = input.logicalDevice.allocateCommandBuffers(allocationInfo)[0];

		return commandBuffer;
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error creating framebuffer: " << err.what() << "\n";

		return nullptr;
	}

	return nullptr;

}


void vkInit::make_frame_command_buffers(CommandBufferInput input, bool debug)
{

	vk::CommandBufferAllocateInfo allocationInfo = {}; 

	allocationInfo.commandPool = input.commandPool; 

	allocationInfo.level = vk::CommandBufferLevel::ePrimary; 

	allocationInfo.commandBufferCount = 1; 

	for (size_t i = 0; i < input.swapchainFrames.size(); i++)
	{
		try
		{
			input.swapchainFrames[i].commandBuffer = input.logicalDevice.allocateCommandBuffers(allocationInfo)[0];

			if (debug)
			{
				std::cout << "Allocated Command buffer [" << i << "] \n";
			}
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "Error allocating FrameBuffer[" << i << "]: " << err.what() << "\n";
		}
	}


}
