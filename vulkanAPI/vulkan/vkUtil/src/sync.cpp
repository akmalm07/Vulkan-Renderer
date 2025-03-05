#include "headers.h"

#include "vkUtil\include\sync.h"

vk::Semaphore vkInit::make_semaphore(vk::Device& logicalDevice, bool debug)
{

	if (debug)
	{
		std::cout << "Creating Semaphore...\n";
	}
	vk::SemaphoreCreateInfo semaphoreInfo = {};

	semaphoreInfo.flags = vk::SemaphoreCreateFlags();

	try
	{
		return logicalDevice.createSemaphore(semaphoreInfo);
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error creating semaphore: " << err.what() << "\n";
		return nullptr;
	}

	return nullptr;

}


vk::Fence vkInit::make_fence(vk::Device& logicalDevice, bool debug)
{

	if (debug)
	{
		std::cout << "Creating Fence...\n";
	}
	vk::FenceCreateInfo fenceInfo = {};

	fenceInfo.flags = vk::FenceCreateFlags() | vk::FenceCreateFlagBits::eSignaled; 

	try
	{
		return logicalDevice.createFence(fenceInfo);
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error creating fence: " << err.what() << "\n";
		return nullptr;
	}

	return nullptr;

}