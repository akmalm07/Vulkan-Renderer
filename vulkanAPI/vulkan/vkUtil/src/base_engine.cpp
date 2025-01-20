#include "pch.h"

#include "vkUtil\include\base_engine.h"
#include "vkInit\include\instance.h"
#include "vkInit\include\logging.h"
#include "vkInit\include\device.h"
#include "vkInit\include\swapchain.h"
#include "vkInit\include\pipeline.h"
#include "vkInit\include\discription.h"
#include "vkUtil\include\framebuffer.h"
#include "vkUtil\include\command.h"
#include "vkUtil\include\window.h"
#include "vkUtil\include\sync.h"
#include "vkUtil\include\scene.h"



BaseEngine::BaseEngine()
{


	_debugMode = true;

	_stride.pos = vkVert::PosStride::STRIDE_2D;
	_stride.col = vkVert::ColorStride::RGB;
	_stride.norm = vkVert::NormalStride::NONE;
	_stride.tex = vkVert::TextureStride::NONE;

	//this->pos = vkVertex::enumerate_pos_stride(ePosStride);
	//this->col = vkVertex::enumerate_color_stride(eColStride);
	//this->norm = vkVertex::enumerate_tex_stride(eTexStride);
	//this->tex = vkVertex::enumerate_normal_stride(eNormStride);


	if (_debugMode) {
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




BaseEngine::BaseEngine(vkVert::StrideBundle stride, int width, int height, bool debug)
{


	_debugMode = debug;

	_stride.pos = stride.pos;
	_stride.col = stride.col;
	_stride.norm = stride.norm;
	_stride.tex = stride.tex;

	//this->pos = vkVertex::enumerate_pos_stride(posStride);
	//this->col = vkVertex::enumerate_color_stride(colStride);
	//this->norm = vkVertex::enumerate_tex_stride(texStride);
	//this->tex = vkVertex::enumerate_normal_stride(normStride);


	if (_debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}

	build_glfw_window(width, height);  

	make_instance(); 

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

}




BaseEngine::BaseEngine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool debug) 
{

	_debugMode = debug;

	_stride.pos = stride.pos;
	_stride.col = stride.col;
	_stride.norm = stride.norm;
	_stride.tex = stride.tex;

	//this->pos = vkVertex::enumerate_pos_stride(posStride);
	//this->col = vkVertex::enumerate_color_stride(colStride);
	//this->norm = vkVertex::enumerate_tex_stride(texStride);
	//this->tex = vkVertex::enumerate_normal_stride(normStride);

	_window.SetWindow(glfwWindow); 


	_debugMode = debug; 


	if (_debugMode) {
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





void BaseEngine::build_glfw_window() 
{ 
	_window.CreateWindow("Vulkan", 800, 600);
}


void BaseEngine::build_glfw_window(int width, int height) 
{ 
	_window.CreateWindow("Vulkan", width, height);
}



void BaseEngine::make_instance() {

	_instance = vkInit::make_instance("VK_INIT", _debugMode);
	_dldi = vk::DispatchLoaderDynamic(_instance, vkGetInstanceProcAddr);

	VkSurfaceKHR vkPresentSurface_cStyle;

	if (glfwCreateWindowSurface(_instance, _window.GetWindow(), nullptr, &vkPresentSurface_cStyle) != VK_SUCCESS)
	{
		if (_debugMode)
		{
			std::cerr << "Failed to abstract _window surface with GLFW! \n";
		}
	}
	else if (_debugMode)
	{
		std::cerr << "Successfully abstracted _window surface with GLFW! \n";
	}

	_vkPresentSurface = vkPresentSurface_cStyle;
}



void BaseEngine::make_debug_messenger() {

	if (!_debugMode) {
		return;
	}

	_debugMessenger = vkInit::make_debug_messenger(_instance, _dldi);
}




void BaseEngine::make_physical_device()
{
	_vkPhysicalDevice = vkInit::choose_physical_device(_instance, _debugMode);

	_vkLogicalDevice = vkInit::create_logical_device(_vkPhysicalDevice, _vkPresentSurface, _debugMode);

	std::vector<vk::Queue> queueList = vkUtil::get_queues(_vkPhysicalDevice, _vkLogicalDevice, _vkPresentSurface, _debugMode);

	_vkGraphicsQueue = queueList[0];
	_vkPresentQueue = queueList[1];

}




void BaseEngine::make_swapchain()
{
	vkInit::SwapChainBundle bundle = vkInit::create_swapchain(_vkLogicalDevice, _vkPhysicalDevice, _vkPresentSurface, _window.GetWidth(), _window.GetHeight(), _debugMode);

	_vkSwapchain = bundle.swapChain;

	_vkSwapchainFormat = bundle.format;

	_vkSwapchainFrames = bundle.frames;

	_vkSwapchainExtent = bundle.extent;

	_maxFramesInFlight = _vkSwapchainFrames.size();

	_frameNum = 0;

}




void BaseEngine::remake_swapchain()
{

	_window.SetBufferWidth(0); 
	_window.SetBufferHeight(0); 

	while (_window.GetBufferWidth() == 0 || _window.GetBufferHeight() == 0)
	{
		_window.waitEvents(); 
	}


	_vkLogicalDevice.waitIdle();

	destroy_swapchain();
	make_swapchain();
	make_framebuffer();
	make_frame_sync_objects();

	vkInit::CommandBufferInput commandBuffInput = { _vkLogicalDevice, _vkCommandPool, _vkSwapchainFrames };

	vkInit::make_frame_command_buffers(commandBuffInput, _debugMode);


}




void BaseEngine::destroy_swapchain()
{

	for (auto& frame : _vkSwapchainFrames)
	{
		_vkLogicalDevice.destroyImageView(frame.imageView);
		_vkLogicalDevice.destroyFramebuffer(frame.framebuffer);

		_vkLogicalDevice.destroySemaphore(frame.vkSemaphoreImageAvaiable);
		_vkLogicalDevice.destroySemaphore(frame.vkSemaphoreRenderFinished);
		_vkLogicalDevice.destroyFence(frame.vkFenceInFlight);

		_vkLogicalDevice.freeCommandBuffers(_vkCommandPool, frame.commandBuffer);//freeing the command buffer (unnessesary)
	}

	_vkLogicalDevice.destroySwapchainKHR(_vkSwapchain);

	_maxFramesInFlight = 0;

	_frameNum = 0;

}




void BaseEngine::make_pipeline()



{
	vkInit::GraphicsPipelineInBundle spesifications = {};

	spesifications.vertShaderPath = "Shaders\\vertex.spv";
	spesifications.fragShaderPath = "Shaders\\fragment.spv";
	spesifications.LogicalDevice =   _vkLogicalDevice;
	spesifications.swapchainExtent = _vkSwapchainExtent;
	spesifications.swapchainFormat = _vkSwapchainFormat;

	vkDiscription::DiscriptorBundle discription = {
			_stride.pos,
			_stride.col,
			_stride.norm,
			_stride.tex,
		false
	};

	std::vector<vkDiscription::DiscriptorBundle> vecOfDescriptions;
	vecOfDescriptions.emplace_back(discription);

	vkInit::GraphicsPipelineOutBundle output = vkInit::create_pipeline(spesifications, vecOfDescriptions, _debugMode);


	_vkPipeline = output.pipeline;

	_vkPipelineLayout = output.pipelineLayout;
	_vkRenderpass = output.renderpass;

}




void BaseEngine::create_command_pool_and_command_buffers()
{

	_vkCommandPool = vkInit::make_command_pool(_vkLogicalDevice, _vkPhysicalDevice, _vkPresentSurface, _debugMode);


	vkInit::CommandBufferInput commandBuffInput = { _vkLogicalDevice, _vkCommandPool, _vkSwapchainFrames };

	vkInit::make_command_buffer(commandBuffInput, _debugMode);


	vkInit::make_frame_command_buffers(commandBuffInput, _debugMode);

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

	renderPassBeginInfo.framebuffer = _vkSwapchainFrames[imageIndex].framebuffer;

	renderPassBeginInfo.renderPass = _vkRenderpass;

	renderPassBeginInfo.renderArea.offset.x = 0;

	renderPassBeginInfo.renderArea.offset.y = 0;

	renderPassBeginInfo.renderArea.extent = _vkSwapchainExtent;

	vk::ClearValue clearColor = { std::array<float, 4>{1.0f, 1.0f, 1.0f, 1.0f} };

	renderPassBeginInfo.clearValueCount = 1;

	renderPassBeginInfo.pClearValues = &clearColor;

	commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);

	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, _vkPipeline);

	vk::Viewport vkViewport = vk::Viewport(0.0f, 0.0f, static_cast<float>(_window.GetBufferWidth()), static_cast<float>(_window.GetBufferHeight()), 0.0f, 1.0f);
	commandBuffer.setViewport(0, vkViewport);

	vk::Rect2D vkScissor = vk::Rect2D({ 0, 0 }, { static_cast<uint32_t>(_window.GetBufferWidth()), static_cast<uint32_t>(_window.GetBufferHeight()) }); 
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

	_vkLogicalDevice.waitForFences(1, &_vkSwapchainFrames[_frameNum].vkFenceInFlight, VK_TRUE, UINT64_MAX);


	uint32_t imageIndex{};


	try 
	{
		vk::ResultValue acquire = _vkLogicalDevice.acquireNextImageKHR
		(
			_vkSwapchain,
			UINT64_MAX,
			_vkSwapchainFrames[_frameNum].vkSemaphoreImageAvaiable,
			nullptr
		);

		imageIndex = acquire.value;
	}
	catch (vk::OutOfDateKHRError& err) 
	{
		std::cout << "swapchain OUT OF DATE " << err.what() << "\n";
		return;
	}
	catch (vk::IncompatibleDisplayKHRError& err) 
	{
		std::cout << "Remakeing swapchain: " << err.what() << "\n";
		remake_swapchain();
		return;
	}
	catch (vk::SystemError& err) 
	{
		std::cout << "Failed to acquire swapchain image: " << err.what() << std::endl;
	}



	vk::CommandBuffer commandBuffer = _vkSwapchainFrames[_frameNum].commandBuffer;

	commandBuffer.reset();

	record_draw_commands(commandBuffer, imageIndex);


	vk::SubmitInfo submitInfo = {};


	vk::Semaphore waitSemaphores[] = { _vkSwapchainFrames[_frameNum].vkSemaphoreImageAvaiable };

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

	submitInfo.waitSemaphoreCount = 1;

	submitInfo.pWaitSemaphores = waitSemaphores;

	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;

	submitInfo.pCommandBuffers = &commandBuffer;

	vk::Semaphore signalSemaphores[] = { _vkSwapchainFrames[_frameNum].vkSemaphoreRenderFinished };

	submitInfo.signalSemaphoreCount = 1;

	submitInfo.pSignalSemaphores = signalSemaphores;


	_vkLogicalDevice.resetFences(1, &_vkSwapchainFrames[_frameNum].vkFenceInFlight);//closing the fence behind it


	try 
	{
		_vkGraphicsQueue.submit(submitInfo, _vkSwapchainFrames[_frameNum].vkFenceInFlight); 
	}
	catch (vk::SystemError& err) {

		if (_debugMode) 
		{
			std::cout << "failed to submit draw command buffer!" << std::endl;
		}
	}

	vk::PresentInfoKHR presentInfo = {};

	presentInfo.waitSemaphoreCount = 1;

	presentInfo.pWaitSemaphores = signalSemaphores;

	vk::SwapchainKHR swapChains[] = { _vkSwapchain };

	presentInfo.swapchainCount = 1;

	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;


	vk::Result present;


	try
	{
		present = _vkPresentQueue.presentKHR(presentInfo);
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


	_frameNum = (_frameNum + 1) % _maxFramesInFlight;

}


void BaseEngine::make_framebuffer()
{
	vkInit::framebufferInput input;
	input.logicalDevice = _vkLogicalDevice;
	input.renderPass = _vkRenderpass;
	input.swapchainExtent = _vkSwapchainExtent;

	for (size_t i = 0; i < _vkSwapchainFrames.size(); i++)
	{
		_vkSwapchainFrames[i].framebuffer = vkInit::make_framebuffer(input, _vkSwapchainFrames[i].imageView, _debugMode);
	}

}


void BaseEngine::make_frame_sync_objects()
{
	for (auto& frame : _vkSwapchainFrames)
	{
		frame.vkSemaphoreImageAvaiable = vkInit::make_semaphore(_vkLogicalDevice, _debugMode);
		frame.vkSemaphoreRenderFinished = vkInit::make_semaphore(_vkLogicalDevice, _debugMode);
		frame.vkFenceInFlight = vkInit::make_fence(_vkLogicalDevice, _debugMode);

	}
}


vk::Device BaseEngine::get_logical_device() const
{
	return _vkLogicalDevice;
}


vk::PhysicalDevice BaseEngine::get_physical_device() const
{
	return _vkPhysicalDevice;
}



BaseEngine::~BaseEngine()
{

	if (_debugMode)
	{
		std::cout << "Goodbye see you!\n";
	}


	destroy_swapchain();


	_vkLogicalDevice.destroyCommandPool(_vkCommandPool);


	_vkLogicalDevice.destroyPipeline(_vkPipeline);

	_vkLogicalDevice.destroyPipelineLayout(_vkPipelineLayout);

	_vkLogicalDevice.destroyRenderPass(_vkRenderpass);




	_instance.destroySurfaceKHR(_vkPresentSurface);

	if (_debugMode)
	{
		_instance.destroyDebugUtilsMessengerEXT(_debugMessenger, nullptr, _dldi);
	}
	/*
	* from vulkan_funcs.hpp:
	*
	* void _instance::destroy( Optional<const VULKAN_HPP_NAMESPACE::AllocationCallbacks> allocator = nullptr,
											Dispatch const & d = ::vk::getDispatchLoaderStatic())
	*/


	_vkLogicalDevice.destroy();

	_instance.destroy();

	//terminate glfw
	glfwTerminate();
}

