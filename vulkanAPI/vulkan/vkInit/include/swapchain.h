#pragma once

#include "pch.h"

#include "vkUtil\include\queue_families.h"
#include "vkInit\include\logging.h"


namespace vkInit
{


	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities; //Determines how much images to swap through, image sizes, etc...
		std::vector<vk::SurfaceFormatKHR> formats; //Determines the supported pixal formats on the screen, EX: RGBA
		std::vector<vk::PresentModeKHR> presentModes; //Determines the algorithm for selecting images to presentgkv

	};



	struct SwapChainBundle
	{
		vk::SwapchainKHR swapChain;
		vk::Format format;
		vk::Extent2D extent;
		std::vector <vkUtil::SwapChainFrame> frames;
	};



	SwapChainSupportDetails query_swapchain_details(const vk::PhysicalDevice& device, vk::SurfaceKHR& surfaace, bool debug);

	vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats);

	vk::PresentModeKHR choose_swapchain_present_mode(std::vector<vk::PresentModeKHR> presentModes);

	vk::Extent2D choose_swapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities);

	SwapChainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice device, vk::SurfaceKHR surface, int width, int height, bool debug);



}
