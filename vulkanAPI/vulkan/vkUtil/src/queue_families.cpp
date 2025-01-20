#include "pch.h"

#include "queue_families.h"


namespace vkUtil
{



	bool QueueFamilyIndices::is_complete()
	{
		return presentFamily.has_value() && graphicsFamily.has_value();
	}




	std::vector<vk::Queue> vkUtil::get_queues(vk::PhysicalDevice& device, vk::Device& logicalDevice, vk::SurfaceKHR& surface, bool debug)
	{
		vkUtil::QueueFamilyIndices queueFamilies = find_queue_families(device, surface, debug);

		return
		{
			logicalDevice.getQueue(queueFamilies.graphicsFamily.value(), 0),
			logicalDevice.getQueue(queueFamilies.presentFamily.value(), 0)
		};
	}



	vkUtil::QueueFamilyIndices vkUtil::find_queue_families(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug)
	{
		vkUtil::QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

		if (debug)
		{
			std::cout << "Device can support " << queueFamilies.size() << " queue families \n";
		}

		int i = 0;
		for (auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
			{
				if (debug)
				{
					std::cout << "\tGraphics Family is supported!\n";
					std::cout << "Queue " << i << " supports graphics \n";
				}


				indices.graphicsFamily = i;
			}

			if (device.getSurfaceSupportKHR(i, surface))
			{
				indices.presentFamily = i;

				if (debug)
				{
					std::cout << "Queue " << i << " supports presenting\n";
				}
			}

			if (indices.is_complete())
			{
				break;
			}

			i++;
		}


		return indices;
	}



} // namespace vkUtil