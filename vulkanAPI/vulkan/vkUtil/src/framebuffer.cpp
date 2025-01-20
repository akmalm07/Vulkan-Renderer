#include "pch.h"

#include "framebuffer.h"

vk::Framebuffer vkInit::make_framebuffer(framebufferInput& input,vk::ImageView& imageView, bool debug)
{
	if (debug)
	{
		std::cout << "Creating FrameBuffer...\n";
	}
	std::vector <vk::ImageView> attachments = {
		imageView
	};

	vk::FramebufferCreateInfo framebufferInfo = {};

	framebufferInfo.flags = vk::FramebufferCreateFlags();

	framebufferInfo.renderPass = input.renderPass;
		
	framebufferInfo.attachmentCount = UINT32(attachments.size());

	framebufferInfo.pAttachments = attachments.data();
		
	framebufferInfo.width = input.swapchainExtent.width;

	framebufferInfo.height = input.swapchainExtent.height;
		 
	framebufferInfo.layers = 1;

	try
	{
		return input.logicalDevice.createFramebuffer(framebufferInfo);
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error creating framebuffer " << ": " << err.what() << "\n";
	}	



}
