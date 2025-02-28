#pragma once

#include "config.h"

#include "vkUtil\include\buffers.h"
#include "vkUtil\include\vertex.h"
#include "tools\include\stride.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\swapchain_frames.h"
#include "vkUtil\include\camera.h"
#include "vkInit\include\descriptor_set_bundles.h"
#include "tools\include\memory_pool.h"
#include "tools\include\memory_pool_container.h"
#include "tools\include\timer.h"
#include "tools\include\thread.h"


#include "tools\include\window.h"


#include <memory>


class BaseEngine 
{

public:

	BaseEngine();

	BaseEngine(int width, int height, bool orthoOrPerpective, bool debug);

	BaseEngine(tools::WindowT& window, bool orthoOrPerpective, bool debug);
	
	BaseEngine(GLFWwindow* glfwWindow, bool orthoOrPerpective, bool debug);

	void render();

	virtual void draw(vk::CommandBuffer& commandBuffer) const = 0;
	
	virtual void game_logic(const double& deltaTime) = 0;
	
	virtual void update_sets(vk::CommandBuffer& commandBuffer) = 0;
	
	virtual bool camera_logic() = 0;

	void update_FPS();

	vk::Device get_logical_device() const;

	vk::PhysicalDevice get_physical_device() const;

	inline bool running() const{ return !_window.GetShouldClose(); }

	virtual ~BaseEngine(); 

protected:

	enum DescriptorSetBuffers : size_t 
	{
		Buffer1,
		BufferCount
	};

	enum Sets
	{
		Set1,
		SetCount

	};
	enum class Set1 : size_t
	{
		Binding1,
		BindingCount
	};




	bool _debugMode = true;

	//glfw window parameters
	tools::WindowT _window;

	tools::CameraT _camera;

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


	const std::filesystem::path _shaderVertPath = UserInput::v_shader_path;  
	const std::filesystem::path _shaderFragPath = UserInput::f_shader_path; 
	const std::filesystem::path _jsonDescriptorSetsFilePath = UserInput::desc_set_json_path;
	const std::filesystem::path _jsonPushCosntantsFilePath = UserInput::push_const_json_path;

	const std::filesystem::path _jsonFileDescriptorSets = "descriptor_sets.json";

	double _deltaTime = 0.0;

	tools::Timer _timer = false;

	//Descriptor Sets
	struct DescriptorSetsStruct
	{
		struct Update
		{
		public:
			Update(size_t id, bool status) : id(id), status(status) {}
			size_t get_id() const { return id; }
			bool status;
		private:
			const size_t id;
		};

		std::array<vk::DescriptorSet, SIZET(SetCount)> sets;
		std::array<std::vector<Update>, SIZET(SetCount)> updated;

	}_vkDescriptorSets;
	std::vector<vk::DescriptorSetLayout> _vkDescriptorSetLayouts;
	vk::DescriptorPool _vkDescriptorPool;
	std::array<vkUtil::Buffer, SIZET(BufferCount)> _vkDescriptorSetBuffers;


	//Push Consts
	std::vector<vkType::PushConst> _vkPushConsts;


	//Syncronization variubles
	size_t _maxFramesInFlight, _frameNum;
	

	//Matrices

	alignas(16) struct Matrices
	{
		glm::mat4 _modelMat;
		glm::mat4 _viewMat;
		glm::mat4 _projMat;
	} _MVPMats;


	// Threads
	struct WindowInputAcync
	{
		std::shared_ptr<tools::ConditionalVariuble> windowInput;
		std::shared_ptr<tools::ConditionalVariuble> updateInputParams;
		std::shared_ptr<std::mutex> lockMtx;
		tools::ThreadT<false, false> threadUpdateParams;
	} _windowInputsAsync;

	protected:

	//glfw setup
	void build_glfw_window();

	void build_glfw_window(int width, int height, bool orthoOrPerpective);

	//instance setup
	void make_instance();

	//debug messenger	
	void make_debug_messenger();
	
	void camera_init(bool orthoOrPerpective);

	void read_json_files();

	void make_physical_device();

	void make_swapchain();

	void remake_swapchain();

	void destroy_swapchain();

	void make_descriptor_sets();

	std::vector <std::shared_ptr< vkInit::DescriptorBuffer >> initalize_descriptor_buffers(const std::vector<vkUtil::BufferInput>&descriptorBuffer);

	void make_push_consts();

	void make_pipeline();

	void create_command_pool_and_command_buffers();

	void make_framebuffer();

	void make_frame_sync_objects();

	void record_draw_commands(vk::CommandBuffer& commandBuffer, uint32_t imageIndex);

	void handle_threads();

	uint32_t gen_desc_id(vk::DescriptorType desc);




};

