#pragma once

#include "headers.h"


namespace vkUtil {

	struct SwapChainFrame
	{
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer framebuffer;
		vk::CommandBuffer commandBuffer;

		//Synchronizations for multi - threading

		vk::Fence vkFenceInFlight;
		vk::Semaphore vkSemaphoreImageAvaiable, vkSemaphoreRenderFinished;

	};

}