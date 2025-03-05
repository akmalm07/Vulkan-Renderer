#pragma once

#include "headers.h"
#include "vkUtil\include\queue_families.h"
#include "vkUtil\include\swapchain_frames.h"


namespace vkInit {

	struct CommandBufferInput
	{
		vk::Device logicalDevice;
		vk::CommandPool commandPool;
		std::vector <vkUtil::SwapChainFrame>& swapchainFrames;  

	};

	vk::CommandPool make_command_pool(vk::Device& logicalDevice, vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug);
	
	vk::CommandBuffer make_command_buffer(CommandBufferInput input, bool debug);
	void make_frame_command_buffers(CommandBufferInput input, bool debug);

}
