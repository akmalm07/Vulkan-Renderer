#pragma once

#include "vkUtil\include\vertex.h"
#include "vkUtil\include\stride.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\swapchain_frames.h"
#include "config.h"


#include "vkUtil\include\window.h"



class BaseEngine 
{

public:

	BaseEngine();

	BaseEngine(vkVert::StrideBundle stride, int width, int height, bool debug);

	BaseEngine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool debug);

	void render();

	virtual void draw(vk::CommandBuffer& commandBuffer) const = 0;


	vk::Device get_logical_device() const;

	vk::PhysicalDevice get_physical_device() const;

	template<vkType::ValidObj T>
	void send_as_push_const(T& data, vk::CommandBuffer cmdBuffer, vk::ShaderStageFlagBits shader, uint32_t offset)
	{
		cmdBuffer.pushConstants(_vkPipelineLayout, shader, offset, sizeof(data), &data); 
	}

	void draw_scene();

	virtual ~BaseEngine(); 

protected: 

	//whether to print debug messages in functions
	bool _debugMode = true;

	//glfw window parameters
	vkUtil::Window _window;  

	//vulkan instance
	vk::Instance _instance = nullptr;
	//debug callback
	vk::DebugUtilsMessengerEXT _debugMessenger = nullptr;
	//dynamic instance dispatcher
	vk::DispatchLoaderDynamic _dldi;
	vk::PhysicalDevice _vkPhysicalDevice = nullptr;

	//vulkan logical device
	vk::Device _vkLogicalDevice = nullptr;

	//vulkan queue to store graphics queue
	vk::Queue _vkGraphicsQueue = nullptr;

	//Queue to present stuff o the screen
	vk::Queue _vkPresentQueue = nullptr;

	//vulkan surface for connecting and cooperationg with the window
	vk::SurfaceKHR _vkPresentSurface = nullptr;

	//vulkan swapchain
	vk::SwapchainKHR _vkSwapchain = nullptr;

	//vulkan swapchain images
	std::vector<vkUtil::SwapChainFrame> _vkSwapchainFrames;

	//vulkanswapchain extent
	vk::Extent2D _vkSwapchainExtent;

	//vulkan swapchain format
	vk::Format _vkSwapchainFormat;


	//vulkan pipeline values

	vk::Pipeline _vkPipeline;

	vk::PipelineLayout _vkPipelineLayout;

	vk::RenderPass _vkRenderpass;

	//Command variubles
	vk::CommandPool _vkCommandPool;
	vk::CommandBuffer _vkMainCommandBuffer;

	vkVert::StrideBundle _stride;


	//uint8_t pos;
	//uint8_t col;
	//uint8_t norm;
	//uint8_t tex;


	//Syncronization variubles
	size_t _maxFramesInFlight, _frameNum;


	//glfw setup
	void build_glfw_window();

	void build_glfw_window(int width, int height);

	//instance setup
	void make_instance();

	//debug messenger	
	void make_debug_messenger();

	void make_physical_device();

	void make_swapchain();

	void remake_swapchain();

	void destroy_swapchain();

	void make_pipeline();

	void create_command_pool_and_command_buffers();

	void make_framebuffer();

	void make_frame_sync_objects();

	void record_draw_commands(vk::CommandBuffer& commandBuffer, uint32_t imageIndex);
};
