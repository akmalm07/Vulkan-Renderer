#include "headers.h"

#include "vkInit\include\swapchain.h"
#include "vkInit\include\logging.h"
#include "vkUtil\include\queue_families.h"


namespace vkInit
{

	SwapChainSupportDetails query_swapchain_details(const vk::PhysicalDevice& device, vk::SurfaceKHR& surface, bool debug)
	{
		SwapChainSupportDetails supportedDetails;

		supportedDetails.capabilities = device.getSurfaceCapabilitiesKHR(surface);

		if (debug)
		{
			std::cout << "Minimum Image Count: " << supportedDetails.capabilities.minImageCount << "\n";
			std::cout << "Maximum Image Count: " << supportedDetails.capabilities.maxImageCount << "\n";

			std::cout << "Current Swapchain extent: \n";
			std::cout << "\tImage Width: " << supportedDetails.capabilities.currentExtent.width << "\n";
			std::cout << "\tImage Height: " << supportedDetails.capabilities.currentExtent.height << "\n";

			std::cout << "Minimum supported Swapchain extent: \n";
			std::cout << "\tImage Width: " << supportedDetails.capabilities.minImageExtent.width << "\n";
			std::cout << "\tImage Height: " << supportedDetails.capabilities.minImageExtent.height << "\n";

			std::cout << "Maximum supported Swapchain extent: \n";
			std::cout << "\tImage Width: " << supportedDetails.capabilities.maxImageExtent.width << "\n";
			std::cout << "\tImage Height: " << supportedDetails.capabilities.maxImageExtent.height << "\n";


			std::cout << "Maximum Array Layers : " << supportedDetails.capabilities.maxImageArrayLayers << "\n";


			std::cout << "Current transforms: \n";
			std::vector<std::string> stringList = log_transform_bits(supportedDetails.capabilities.currentTransform);

			for (const auto& line : stringList)
			{
				std::cout << "\t" << line << "\n";
			}


			std::cout << "Supported transforms: \n";
			stringList = log_transform_bits(supportedDetails.capabilities.supportedTransforms);

			for (const auto& line : stringList)
			{
				std::cout << "\t" << line << "\n";
			}

			std::cout << "Supported alpha bits: \n";
			stringList = log_alpha_composite_bits(supportedDetails.capabilities.supportedCompositeAlpha);

			for (const auto& line : stringList)
			{
				std::cout << "\t" << line << "\n";
			}

			std::cout << "Supported usage: \n";
			stringList = log_image_usage_bits(supportedDetails.capabilities.supportedUsageFlags);

			for (const auto& line : stringList)
			{
				std::cout << "\t" << line << "\n";
			}


			supportedDetails.formats = device.getSurfaceFormatsKHR(surface);

			for (const auto& supportedFormat : supportedDetails.formats)
			{

				std::cout << "\tSupported pixal format: " << vk::to_string(supportedFormat.format) << " \n";
				std::cout << "\tSupported color space: " << vk::to_string(supportedFormat.colorSpace) << " \n";
			}


			supportedDetails.presentModes = device.getSurfacePresentModesKHR(surface);

			std::cout << "Supported present modes: \n";
			for (const auto& supportedPresentModes : supportedDetails.presentModes)
			{
				std::cout << "\t" << log_present_mode(supportedPresentModes) << " \n";
			}

		}


		return supportedDetails;
	}

	vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats)
	{
		for (vk::SurfaceFormatKHR format : formats) {
			if (format.format == vk::Format::eB8G8R8A8Unorm
				&& format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				return format;
			}
		}

		return formats[0];
	}


	vk::PresentModeKHR choose_swapchain_present_mode(std::vector<vk::PresentModeKHR> presentModes)
	{

		for (vk::PresentModeKHR presentMode : presentModes) {
			if (presentMode == vk::PresentModeKHR::eMailbox) {
				return presentMode;
			}
		}

		return vk::PresentModeKHR::eFifo;
	}




	vk::Extent2D choose_swapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities) {

		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			vk::Extent2D extent = { width, height };

			extent.width = std::min(
				capabilities.maxImageExtent.width,
				std::max(capabilities.minImageExtent.width, extent.width)
			);

			extent.height = std::min(
				capabilities.maxImageExtent.height,
				std::max(capabilities.minImageExtent.height, extent.height)
			);

			return extent;
		}
	}




	SwapChainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice device, vk::SurfaceKHR surface, int width, int height, bool debug)
	{
		SwapChainSupportDetails swapchainData = query_swapchain_details(device, surface, debug);

		vk::SurfaceFormatKHR format = choose_swapchain_surface_format(swapchainData.formats);

		vk::PresentModeKHR presentMode = choose_swapchain_present_mode(swapchainData.presentModes);

		vk::Extent2D extent = choose_swapchain_extent(height, width, swapchainData.capabilities);

		uint32_t imageCount = std::min
		(
			swapchainData.capabilities.maxImageCount,
			swapchainData.capabilities.minImageCount + 1
		);

		vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR
		(
			vk::SwapchainCreateFlagsKHR(),
			surface,
			imageCount,
			format.format,
			format.colorSpace,
			extent,
			1,
			vk::ImageUsageFlagBits::eColorAttachment
		);

		vkUtil::QueueFamilyIndices indices = vkUtil::find_queue_families(device, surface, debug);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily.value() != indices.graphicsFamily.value())
		{
			createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = vk::SharingMode::eExclusive;
		}

		createInfo.preTransform = swapchainData.capabilities.currentTransform;
		createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = vk::SwapchainKHR(nullptr);


		SwapChainBundle swapchain{};

		try
		{
			swapchain.swapChain = logicalDevice.createSwapchainKHR(createInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cout << "Error creating SwapChain: " << err.what() << "\n";
			throw std::runtime_error("Error creating swapchains!");
		}


		std::vector <vk::Image> images = logicalDevice.getSwapchainImagesKHR(swapchain.swapChain);

		swapchain.frames.resize(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{

			vk::ImageViewCreateInfo imageInfo{};

			imageInfo.image = images[i];
			imageInfo.viewType = vk::ImageViewType::e2D;
			imageInfo.components.r = vk::ComponentSwizzle::eIdentity;
			imageInfo.components.g = vk::ComponentSwizzle::eIdentity;
			imageInfo.components.b = vk::ComponentSwizzle::eIdentity;
			imageInfo.components.a = vk::ComponentSwizzle::eIdentity;
			imageInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
			imageInfo.subresourceRange.baseMipLevel = 0;
			imageInfo.subresourceRange.levelCount = 1;
			imageInfo.subresourceRange.baseArrayLayer = 0;
			imageInfo.subresourceRange.layerCount = 1;
			imageInfo.format = format.format;

			swapchain.frames[i].image = images[i];

			swapchain.frames[i].imageView = logicalDevice.createImageView(imageInfo);




		}

		swapchain.format = format.format;
		swapchain.extent = extent;


		return swapchain;
	}


}