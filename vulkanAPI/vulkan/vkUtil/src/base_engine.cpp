#include "vkUtil\include\base_engine.h"
#include "vkInit\include\instance.h"
#include "vkInit\include\logging.h"
#include "vkInit\include\device.h"
#include "vkInit\include\swapchain.h"
#include "vkInit\include\pipeline.h"
#include "vkInit\include\discription.h"
#include "vkUtil\include\framebuffer.h"
#include "vkUtil\include\command.h"
#include "vkUtil\include\sync.h"
#include "vkUtil\include\scene.h"



BaseEngine::BaseEngine()
{


	debugMode = true;

	ePosStride = vkVertex::PosStride::STRIDE_2D;
	eColStride = vkVertex::ColorStride::RGB;
	eNormStride = vkVertex::NormalStride::NONE;
	eTexStride = vkVertex::TextureStride::NONE;

	this->pos = vkVertex::enumerate_pos_stride(ePosStride);
	this->col = vkVertex::enumerate_color_stride(eColStride);
	this->norm = vkVertex::enumerate_tex_stride(eTexStride);
	this->tex = vkVertex::enumerate_normal_stride(eNormStride);


	if (debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}

	build_glfw_window();

	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();
}




BaseEngine::BaseEngine(vkVertex::PosStride posStride, vkVertex::ColorStride colStride, vkVertex::NormalStride normStride,
	vkVertex::TextureStride texStride, bool debug)
{


	debugMode = debug;

	this->ePosStride = posStride;
	this->eColStride = colStride;
	this->eNormStride = normStride;
	this->eTexStride = texStride;

	this->pos = vkVertex::enumerate_pos_stride(posStride);
	this->col = vkVertex::enumerate_color_stride(colStride);
	this->norm = vkVertex::enumerate_tex_stride(texStride);
	this->tex = vkVertex::enumerate_normal_stride(normStride);


	if (debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}

	build_glfw_window();

	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

}




BaseEngine::BaseEngine(GLFWwindow* glfwWindow, vkVertex::PosStride posStride,
	vkVertex::ColorStride colStride, vkVertex::NormalStride normStride, vkVertex::TextureStride texStride, bool debug)
{



	this->ePosStride = posStride;
	this->eColStride = colStride;
	this->eNormStride = normStride;
	this->eTexStride = texStride;

	this->pos = vkVertex::enumerate_pos_stride(posStride);
	this->col = vkVertex::enumerate_color_stride(colStride);
	this->norm = vkVertex::enumerate_tex_stride(texStride);
	this->tex = vkVertex::enumerate_normal_stride(normStride);

	window = glfwWindow;

	glfwGetWindowSize(glfwWindow, &windowWidth, &windowHeight);


	debugMode = debug;


	if (debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}


	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();
}





void BaseEngine::build_glfw_window() {

	//initialize glfw
	
}



void BaseEngine::make_instance() {

	instance = vkInit::make_instance(debugMode, "ID Tech 12");
	dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

	VkSurfaceKHR vkPresentSurface_cStyle;

	if (glfwCreateWindowSurface(instance, window, nullptr, &vkPresentSurface_cStyle) != VK_SUCCESS)
	{
		if (debugMode)
		{
			std::cerr << "Failed to abstract window surface with GLFW! \n";
		}
	}
	else if (debugMode)
	{
		std::cerr << "Successfully abstracted window surface with GLFW! \n";
	}

	vkPresentSurface = vkPresentSurface_cStyle;
}



void BaseEngine::make_debug_messenger() {

	if (!debugMode) {
		return;
	}

	debugMessenger = vkInit::make_debug_messenger(instance, dldi);
}




void BaseEngine::make_physical_device()
{
	vkPhysicalDevice = vkInit::choose_physical_device(instance, debugMode);

	vkLogicalDevice = vkInit::create_logical_device(vkPhysicalDevice, vkPresentSurface, debugMode);

	std::vector<vk::Queue> queueList = vkUtil::get_queues(vkPhysicalDevice, vkLogicalDevice, vkPresentSurface, debugMode);

	vkGraphicsQueue = queueList[0];
	vkPresentQueue = queueList[1];

}




void BaseEngine::make_swapchain()
{
	vkInit::SwapChainBundle bundle = vkInit::create_swapchain(vkLogicalDevice, vkPhysicalDevice, vkPresentSurface, windowWidth, windowHeight, debugMode);

	vkSwapchain = bundle.swapChain;

	vkSwapchainFormat = bundle.format;

	vkSwapchainFrames = bundle.frames;

	vkSwapchainExtent = bundle.extent;

	maxFramesInFlight = vkSwapchainFrames.size();

	frameNum = 0;

}




void BaseEngine::remake_swapchain()
{

	windowWidth = 0;
	windowHeight = 0;

	while (windowWidth == 0 || windowHeight == 0)
	{
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glfwWaitEvents();
	}


	vkLogicalDevice.waitIdle();

	destroy_swapchain();
	make_swapchain();
	make_framebuffer();
	make_frame_sync_objects();

	vkInit::CommandBufferInput commandBuffInput = { vkLogicalDevice, vkCommandPool, vkSwapchainFrames };

	vkInit::make_frame_command_buffers(commandBuffInput, debugMode);


}




void BaseEngine::destroy_swapchain()
{

	for (auto& frame : vkSwapchainFrames)
	{
		vkLogicalDevice.destroyImageView(frame.imageView);
		vkLogicalDevice.destroyFramebuffer(frame.framebuffer);

		vkLogicalDevice.destroySemaphore(frame.vkSemaphoreImageAvaiable);
		vkLogicalDevice.destroySemaphore(frame.vkSemaphoreRenderFinished);
		vkLogicalDevice.destroyFence(frame.vkFenceInFlight);

		vkLogicalDevice.freeCommandBuffers(vkCommandPool, frame.commandBuffer);//freeing the command buffer (unnessesary)
	}

	vkLogicalDevice.destroySwapchainKHR(vkSwapchain);

	maxFramesInFlight = 0;

	frameNum = 0;

}




void BaseEngine::make_pipeline()



{
	vkInit::GraphicsPipelineInBundle spesifications = {};

	spesifications.vertShaderPath = "Shaders\\vertex.spv";
	spesifications.fragShaderPath = "Shaders\\fragment.spv";
	spesifications.LogicalDevice = vkLogicalDevice;
	spesifications.swapchainExtent = vkSwapchainExtent;
	spesifications.swapchainFormat = vkSwapchainFormat;

	vkDiscription::DiscriptorBundle discription = {
		ePosStride,
		eColStride,
		eNormStride,
		eTexStride,
		false
	};

	std::vector< vkDiscription::DiscriptorBundle> vecOfDescriptions;
	vecOfDescriptions.emplace_back(discription);

	vkInit::GraphicsPipelineOutBundle output = vkInit::create_pipeline(spesifications, vecOfDescriptions, debugMode);


	vkPipeline = output.pipeline;

	vkPipelineLayout = output.pipelineLayout;
	vkRenderpass = output.renderpass;

}




void BaseEngine::create_command_pool_and_command_buffers()
{

	vkCommandPool = vkInit::make_command_pool(vkLogicalDevice, vkPhysicalDevice, vkPresentSurface, debugMode);


	vkInit::CommandBufferInput commandBuffInput = { vkLogicalDevice, vkCommandPool, vkSwapchainFrames };

	vkInit::make_command_buffer(commandBuffInput, debugMode);


	vkInit::make_frame_command_buffers(commandBuffInput, debugMode);

	make_frame_sync_objects();



}




void BaseEngine::record_draw_commands(vk::CommandBuffer& commandBuffer, uint32_t imageIndex)
{
	vk::CommandBufferBeginInfo commandBufferBeginInfo = {};

	try
	{
		commandBuffer.begin(commandBufferBeginInfo);
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error beginning command buffer: " << err.what() << "\n";

	}

	vk::RenderPassBeginInfo renderPassBeginInfo = {};

	renderPassBeginInfo.framebuffer = vkSwapchainFrames[imageIndex].framebuffer;

	renderPassBeginInfo.renderPass = vkRenderpass;

	renderPassBeginInfo.renderArea.offset.x = 0;

	renderPassBeginInfo.renderArea.offset.y = 0;

	renderPassBeginInfo.renderArea.extent = vkSwapchainExtent;

	vk::ClearValue clearColor = { std::array<float, 4>{1.0f, 1.0f, 1.0f, 1.0f} };

	renderPassBeginInfo.clearValueCount = 1;

	renderPassBeginInfo.pClearValues = &clearColor;

	commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);

	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, vkPipeline);

	vk::Viewport vkViewport = vk::Viewport(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f, 1.0f);
	commandBuffer.setViewport(0, vkViewport);

	vk::Rect2D vkScissor = vk::Rect2D({ 0, 0 }, { static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight) });
	commandBuffer.setScissor(0, vkScissor);

	draw(commandBuffer);

	commandBuffer.endRenderPass();

	try
	{
		commandBuffer.end();
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error Ending the Command Buffer: " << err.what() << "\n";
	}



}



void BaseEngine::render()
{

	vkLogicalDevice.waitForFences(1, &vkSwapchainFrames[frameNum].vkFenceInFlight, VK_TRUE, UINT64_MAX);


	uint32_t imageIndex{};


	try {
		vk::ResultValue acquire = vkLogicalDevice.acquireNextImageKHR
		(
			vkSwapchain,
			UINT64_MAX,
			vkSwapchainFrames[frameNum].vkSemaphoreImageAvaiable,
			nullptr
		);

		imageIndex = acquire.value;
	}
	catch (vk::OutOfDateKHRError& err) {
		std::cout << "swapchain OUT OF DATE " << err.what() << "\n";
		return;
	}
	catch (vk::IncompatibleDisplayKHRError& err) {
		std::cout << "Remakeing swapchain: " << err.what() << "\n";
		remake_swapchain();
		return;
	}
	catch (vk::SystemError& err) {
		std::cout << "Failed to acquire swapchain image: " << err.what() << std::endl;
	}



	vk::CommandBuffer commandBuffer = vkSwapchainFrames[frameNum].commandBuffer;

	commandBuffer.reset();

	record_draw_commands(commandBuffer, imageIndex);


	vk::SubmitInfo submitInfo = {};


	vk::Semaphore waitSemaphores[] = { vkSwapchainFrames[frameNum].vkSemaphoreImageAvaiable };

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

	submitInfo.waitSemaphoreCount = 1;

	submitInfo.pWaitSemaphores = waitSemaphores;

	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;

	submitInfo.pCommandBuffers = &commandBuffer;

	vk::Semaphore signalSemaphores[] = { vkSwapchainFrames[frameNum].vkSemaphoreRenderFinished };

	submitInfo.signalSemaphoreCount = 1;

	submitInfo.pSignalSemaphores = signalSemaphores;


	vkLogicalDevice.resetFences(1, &vkSwapchainFrames[frameNum].vkFenceInFlight);//closing the fence behind it


	try {
		vkGraphicsQueue.submit(submitInfo, vkSwapchainFrames[frameNum].vkFenceInFlight);
	}
	catch (vk::SystemError err) {

		if (debugMode) {
			std::cout << "failed to submit draw command buffer!" << std::endl;
		}
	}

	vk::PresentInfoKHR presentInfo = {};

	presentInfo.waitSemaphoreCount = 1;

	presentInfo.pWaitSemaphores = signalSemaphores;

	vk::SwapchainKHR swapChains[] = { vkSwapchain };

	presentInfo.swapchainCount = 1;

	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;


	vk::Result present;


	try
	{
		present = vkPresentQueue.presentKHR(presentInfo);
	}
	catch (vk::OutOfDateKHRError& err)
	{
		std::cout << "Swapchain out of date: " << err.what() << "\n";
		present = vk::Result::eErrorOutOfDateKHR;
	}
	catch (vk::SystemError& err)
	{
		std::cerr << "Error presenting the present queue: " << err.what() << "\n";
	}


	if (present == vk::Result::eErrorOutOfDateKHR || present == vk::Result::eSuboptimalKHR) {
		remake_swapchain();
		return;
	}


	frameNum = (frameNum + 1) % maxFramesInFlight;

}




void BaseEngine::make_framebuffer()
{
	vkInit::framebufferInput input;
	input.logicalDevice = vkLogicalDevice;
	input.renderPass = vkRenderpass;
	input.swapchainExtent = vkSwapchainExtent;

	for (size_t i = 0; i < vkSwapchainFrames.size(); i++)
	{
		vkSwapchainFrames[i].framebuffer = vkInit::make_framebuffer(input, vkSwapchainFrames[i].imageView, debugMode);
	}

}



void BaseEngine::make_frame_sync_objects()
{
	for (auto& frame : vkSwapchainFrames)
	{
		frame.vkSemaphoreImageAvaiable = vkInit::make_semaphore(vkLogicalDevice, debugMode);
		frame.vkSemaphoreRenderFinished = vkInit::make_semaphore(vkLogicalDevice, debugMode);
		frame.vkFenceInFlight = vkInit::make_fence(vkLogicalDevice, debugMode);

	}
}





vk::Device BaseEngine::get_logical_device() const
{
	return vkLogicalDevice;
}





vk::PhysicalDevice BaseEngine::get_physical_device() const
{
	return vkPhysicalDevice;
}




void BaseEngine::draw_scene()
{

}

void BaseEngine::intial_clean_up()
{
	vkLogicalDevice.waitIdle();
}





BaseEngine::~BaseEngine()
{

	if (debugMode)
	{
		std::cout << "Goodbye see you!\n";
	}


	destroy_swapchain();


	vkLogicalDevice.destroyCommandPool(vkCommandPool);


	vkLogicalDevice.destroyPipeline(vkPipeline);

	vkLogicalDevice.destroyPipelineLayout(vkPipelineLayout);

	vkLogicalDevice.destroyRenderPass(vkRenderpass);




	instance.destroySurfaceKHR(vkPresentSurface);

	if (debugMode)
	{
		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
	}
	/*
	* from vulkan_funcs.hpp:
	*
	* void Instance::destroy( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator = nullptr,
											Dispatch const & d = ::vk::getDispatchLoaderStatic())
	*/


	vkLogicalDevice.destroy();

	instance.destroy();

	//terminate glfw
	glfwTerminate();
}

