#pragma once

#include "pch.h"



namespace vkInit {

	bool is_device_suitable(vk::PhysicalDevice& device, bool debug);
	
	bool check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& extensions, bool debug);
	
	vk::Device create_logical_device(vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug);

	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

}
