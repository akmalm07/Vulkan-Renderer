#pragma once

#include "config.h"

#include "vkInit\include\swapchain.h"





namespace vkInit {

	struct framebufferInput
	{
		vk::Device logicalDevice;
		vk::Extent2D swapchainExtent;
		vk::RenderPass renderPass;
	};


	vk::Framebuffer make_framebuffer(framebufferInput& input, vk::ImageView& imageView, bool debug);

}