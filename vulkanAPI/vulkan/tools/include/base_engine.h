#pragma once

#include "config.h"

#include "vkUtil\include\vertex.h"
#include "tools\include\stride.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\swapchain_frames.h"
#include "vkUtil\include\camera.h"


#include "tools\include\window.h"



class BaseEngine 
{

public:

	BaseEngine();

	BaseEngine(vkVert::StrideBundle stride, int width, int height, bool orthoOrPerpective, bool debug);

	BaseEngine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool orthoOrPerpective, bool debug);

	void render();

	virtual void draw(vk::CommandBuffer& commandBuffer) const = 0;

	void updateFPS();

	vk::Device get_logical_device() const;

	vk::PhysicalDevice get_physical_device() const;

	inline bool running() const{ return !_window.GetShouldClose(); }

	virtual ~BaseEngine(); 

protected: 

	bool _debugMode = true;

	//glfw window parameters
	vkUtil::WindowT _window;

	vkUtil::CameraT _camera;

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

	const std::filesystem::path _shaderVertPath = UserInput::v_shader_path;  
	const std::filesystem::path _shaderFragPath = UserInput::f_shader_path; 
	const std::filesystem::path _jsonFileDescriptorSets = "descriptor_sets.json";

	std::string rawJson = R"({
  "descriptor_sets": [
    {
      "bindings": [
        {
          "binding": 0,
          "descriptor_type": "uniform_buffer",
          "descriptor_count": 1,
          "stage_flags": "vertex"
        }
      ]

    }


  ],
  "layouts": [

    {
      "bindings": [
        {
          "binding": 0,
          "descriptor_type": "uniform_buffer",
          "descriptor_count": 1,
          "stage_flags": "vertex"
        }
      ]

    }
  ] 
 
})";

	//Descriptor Sets
	std::vector<vk::DescriptorSet> _vkDescriptorSets;
	std::vector<vk::DescriptorSetLayout> _vkDescriptorSetLayouts;
	vk::DescriptorPool _vkDescriptorPool;

	//Push Consts
	std::vector<vkType::PushConst> _vkPushConsts;


	//Syncronization variubles
	size_t _maxFramesInFlight, _frameNum;


	//glfw setup
	void build_glfw_window();

	void build_glfw_window(int width, int height);

	//instance setup
	void make_instance();

	//debug messenger	
	void make_debug_messenger();

	void read_json_files();

	void make_physical_device();

	void make_swapchain();

	void remake_swapchain();

	void destroy_swapchain();

	void make_descriptor_sets_and_push_consts();

	void make_pipeline();

	void create_command_pool_and_command_buffers();

	void make_framebuffer();

	void make_frame_sync_objects();

	void record_draw_commands(vk::CommandBuffer& commandBuffer, uint32_t imageIndex);


	void is_ortho(bool orthoOrPerpective);
};
