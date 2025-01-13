#pragma once

#include "config.h"


namespace vkUtil {
	struct QueueFamilyIndices
	{
		std::optional <uint32_t> graphicsFamily;
		std::optional <uint32_t> presentFamily;

		bool is_complete();


	};

	
	std::vector<vk::Queue> get_queues(vk::PhysicalDevice& device, vk::Device& logicalDevice, vk::SurfaceKHR& surface, bool debug);

	vkUtil::QueueFamilyIndices find_queue_families(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug);

}