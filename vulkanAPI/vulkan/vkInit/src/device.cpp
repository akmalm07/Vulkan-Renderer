#include "headers.h"

#include "vkInit\include\device.h"
#include "vkInit\include\logging.h"
#include "vkUtil\include\queue_families.h" 




namespace vkInit
{

	vk::Device create_logical_device(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug)
	{

		vkUtil::QueueFamilyIndices queueFamilies = vkUtil::find_queue_families(device, surface, debug);

		std::vector<uint32_t> uniqueQueues;

		uniqueQueues.push_back(queueFamilies.graphicsFamily.value());

		if (queueFamilies.graphicsFamily.value() != queueFamilies.presentFamily.value())
		{
			uniqueQueues.push_back(queueFamilies.presentFamily.value());
		}

		float queuePriority = 1.0f;

		std::vector<vk::DeviceQueueCreateInfo> queueInfo;

		for (auto& uniqueQueue : uniqueQueues)
			queueInfo.push_back
			(
				vk::DeviceQueueCreateInfo
				(
					vk::DeviceQueueCreateFlags(),
					uniqueQueue,
					1,
					&queuePriority
				)
			);

		//we can modifyt the values to disired features
		vk::PhysicalDeviceFeatures deviceFeatures = vk::PhysicalDeviceFeatures();

		std::vector<const char*> enabledLayers;

		std::vector<const char*> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		if (debug)
		{
			enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
		}

		vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo
		(
			vk::DeviceCreateFlags(),
			UINT32(queueInfo.size()),
			queueInfo.data(),
			UINT32(enabledLayers.size()),
			enabledLayers.data(),
			UINT32(deviceExtensions.size()),
			deviceExtensions.data(),
			&deviceFeatures
		);

		try
		{
			vk::Device logicalDevice = device.createDevice(deviceInfo);

			if (debug)
			{
				std::cout << "Successfully created Logical device! \n";
			}
			return logicalDevice;
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "An error occured while creating l;ogicla device: " << err.what() << "\n";
			return nullptr;
		}

		return nullptr;
	}




	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug)
	{

		if (debug)
		{
			std::cout << "Choosing phyical device... \n";
		}

		std::vector<vk::PhysicalDevice> physicalDevices = instance.enumeratePhysicalDevices();

		if (debug)
		{
			std::cout << "Your system has " << physicalDevices.size() << "\n";

		}

		for (auto& device : physicalDevices)
		{
			if (debug)
			{
				log_device_properties(device);
			}

			if (is_device_suitable(device, debug))
			{
				return device;
			}
		}




		return nullptr;
	}





	bool is_device_suitable(vk::PhysicalDevice& device, bool debug)
	{

		if (debug)
		{
			std::cout << "CHecking if device is suitable... \n";
		}

		const std::vector<const char*> requestedExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		std::cout << "Reqiored extensions: ";

		if (debug)
		{
			for (const auto& extension : requestedExtensions)
			{
				std::cout << "\t\" " << extension << "\"\n";
			}
		}


		bool supportedExtensions = check_device_extension_support(device, requestedExtensions, debug);

		if (supportedExtensions)
		{
			if (debug)
			{
				std::cout << "The extensions are supported!\n";
			}
			return true;
		}
		else
		{
			if (debug)
			{
				std::cout << "The extensions are NOT supported!\n";
			}
			return false;
		}

	}

	bool check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& extensions, bool debug)
	{
		std::set<std::string> requioredExtensions(extensions.begin(), extensions.end());

		if (debug)
		{
			std::cout << "The following extensions are supported: \n";
		}

		for (auto& extension : device.enumerateDeviceExtensionProperties())
		{
			if (debug)
			{
				std::cout << "\t\"" << extension.extensionName << "\"\n";
			}


			requioredExtensions.erase(extension.extensionName);
		}

		return requioredExtensions.empty();

	}

}