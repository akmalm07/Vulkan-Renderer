#pragma once

#include "pch.h"
#include "vkUtil\include\vertex.h"
#include "vkType\include\stride.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\scene.h"






class BaseEngine 
{

public:

	BaseEngine();

	BaseEngine(vkVert::PosStride posStride, vkVert::ColorStride colStride,
		vkVert::NormalStride normStride, vkVert::TextureStride texStride, bool debug);

	BaseEngine(GLFWwindow* glfwWindow,
		vkVertex::PosStride posStride, vkVertex::ColorStride colStride, vkVertex::NormalStride normStride,
		vkVertex::TextureStride texStride, bool debug);


	void render();

	virtual void draw(vk::CommandBuffer& commandBuffer) = 0;



	vk::Device get_logical_device() const;

	vk::PhysicalDevice get_physical_device() const;

	template<class T>
	void send_as_push_const(T& data, vk::CommandBuffer cmdBuffer, vk::ShaderStageFlagBits shader, uint32_t offset)
	{
		cmdBuffer.pushConstants(vkPipelineLayout, shader, offset, sizeof(data), &data); 
	}

	//void load_meshes(std::vector<SMesh<T>>& meshes);


	//void load_meshes(std::vector<Mesh<T, U, V, W>>& meshes);

	void draw_scene();

	void intial_clean_up();

	virtual ~BaseEngine(); 

protected: 

	//whether to print debug messages in functions
	bool debugMode = true;

	//glfw window parameters
	int windowWidth = 640;
	int windowHeight = 480;
	GLFWwindow* window = nullptr;

	//vulkan instance
	vk::Instance instance = nullptr;
	//debug callback
	vk::DebugUtilsMessengerEXT debugMessenger = nullptr;
	//dynamic instance dispatcher
	vk::DispatchLoaderDynamic dldi;
	vk::PhysicalDevice vkPhysicalDevice = nullptr;

	//vulkan logical device
	vk::Device vkLogicalDevice = nullptr;

	//vulkan queue to store graphics queue
	vk::Queue vkGraphicsQueue = nullptr;

	//Queue to present stuff o the screen
	vk::Queue vkPresentQueue = nullptr;

	//vulkan surface for connecting and cooperationg with the window
	vk::SurfaceKHR vkPresentSurface = nullptr;

	//vulkan swapchain
	vk::SwapchainKHR vkSwapchain = nullptr;

	//vulkan swapchain images
	std::vector<vkUtil::SwapChainFrame> vkSwapchainFrames;

	//vulkanswapchain extent
	vk::Extent2D vkSwapchainExtent;

	//vulkan swapchain format
	vk::Format vkSwapchainFormat;


	//vulkan pipeline values

	vk::Pipeline vkPipeline;

	vk::PipelineLayout vkPipelineLayout;

	vk::RenderPass vkRenderpass;

	//Command variubles
	vk::CommandPool vkCommandPool;
	vk::CommandBuffer vkMainCommandBuffer;

	vkVertex::PosStride     ePosStride;
	vkVertex::ColorStride   eColStride;
	vkVertex::NormalStride  eNormStride;
	vkVertex::TextureStride eTexStride;


	uint8_t pos;
	uint8_t col;
	uint8_t norm;
	uint8_t tex;


	//Syncronization variubles
	size_t maxFramesInFlight, frameNum;


protected:
	//glfw setup
	void build_glfw_window();

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


