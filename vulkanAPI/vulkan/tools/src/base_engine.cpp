#include "pch.h"

#include "tools\include\base_engine.h"
#include "vkInit\include\instance.h"
#include "vkInit\include\logging.h"
#include "vkInit\include\device.h"
#include "vkInit\include\swapchain.h"
#include "vkInit\include\pipeline.h"
#include "vkInit\include\discription.h"
#include "vkUtil\include\framebuffer.h"
#include "vkUtil\include\command.h"
#include "tools\include\window.h"
#include "vkUtil\include\sync.h"
#include "tools\include\scene.h"
#include "vkUtil\include\render_structs.h"
#include "tools\include\const_push_registry.h"
#include "tools\include\descriptor_set_registry.h"
#include "vkInit\include\descriptor_set.h"
#include "vkInit\include\descriptor_set_bundles.h"
#include "vkUtil\include\pipeline_bundles.h"
#include "vkUtil\include\camera.h"
#include "tools\include\timer.h"
#include "tools\include\json_reader.h"
#include "vkUtil\include\memory.h"
#include "tools\include\memory_pool.h"
#include "tools\include\memory_pool_container.h"



BaseEngine::BaseEngine()
{
	
	_debugMode = true;

	if (_debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}

	build_glfw_window();

	camera_init(true);

	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	read_json_files();
	
	make_push_consts();

	make_descriptor_sets();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

	handle_threads();

}




BaseEngine::BaseEngine(int width, int height, bool orthoOrPerpective, bool debug) 
{

	_debugMode = debug;

	if (_debugMode) {
		std::cout << "Making a graphics BaseEngine\n"; 
	}

	build_glfw_window(width, height, orthoOrPerpective);

	camera_init(orthoOrPerpective); 

	make_instance(); 

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	read_json_files();

	make_push_consts();

	make_descriptor_sets();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

	handle_threads();

}

BaseEngine::BaseEngine(tools::WindowT& glfwWindow, bool orthoOrPerpective, bool debug)
{
	camera_init(orthoOrPerpective);


	_debugMode = debug;

	_window = std::move(glfwWindow);
	_window.CreateWindow(true);


	_debugMode = debug;


	if (_debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}


	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	read_json_files();

	make_push_consts();

	make_descriptor_sets();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

	handle_threads();
}




BaseEngine::BaseEngine(GLFWwindow* glfwWindow, bool orthoOrPerpective, bool debug) 
{

	camera_init(orthoOrPerpective);


	_debugMode = debug;

	_window = std::move(tools::WindowT(800, 800, "Vulkan", true));
	_window.SetWindow(glfwWindow, orthoOrPerpective);


	_debugMode = debug; 


	if (_debugMode) {
		std::cout << "Making a graphics BaseEngine\n";
	}


	make_instance();

	make_debug_messenger();

	make_physical_device();

	make_swapchain();

	read_json_files();

	make_push_consts();

	make_descriptor_sets();

	make_pipeline();

	make_framebuffer();

	create_command_pool_and_command_buffers();

	handle_threads();
}



void BaseEngine::update_FPS()
{
	static double time = 0;
	static uint32_t frameCount = 0;

	time += _deltaTime;
	frameCount++;
	
	if (time >= 1.0) 
	{
		std::stringstream title;
		title << _window.GetName() << " - FPS: " << frameCount;
		_window.SetName(title.str().c_str());

		frameCount = 0;
		time = 0;
	}
}


void BaseEngine::build_glfw_window() 
{ 
	_window = std::move(tools::WindowT(800, 800, "Untitled Window", true));
	_window.CreateWindow(true);
}


void BaseEngine::build_glfw_window(int width, int height, bool orthoOrPerpective)
{ 
	_window = std::move(tools::WindowT(width, height, "Vulkan", orthoOrPerpective));
	_window.CreateWindow(true);
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



void BaseEngine::make_debug_messenger()
{

	if (!_debugMode)
	{
		return;
	}

	_debugMessenger = vkInit::make_debug_messenger(_instance, _dldi);
}

void BaseEngine::read_json_files() 
{
	JsonReader decriptorSet(_jsonDescriptorSetsFilePath);

	std::vector<vkInit::DescriptorSetBindings> descriptorSets;

	for (const auto& set : decriptorSet["descriptor_sets"])
	{
		vkInit::DescriptorSetBindings descriptorSet;
		for (const auto& binding : set["bindings"])
		{
			if (binding["stage_flags"].is_array())
			{
				std::vector<vkUtil::ShaderStage> stages;
				for (const auto& stage : binding["stage_flags"])
				{
					stages.emplace_back(vkUtil::to_shader_stage(stage.get<std::string_view>()));
				}
				descriptorSet.emplace_back
				(
					vkInit::to_descriptor_type(binding["descriptor_type"]),
					stages,
					binding["descriptor_count"].get<uint32_t>(),
					binding["binding"].get<uint32_t>()
				);
			}
			else
			{
				descriptorSet.emplace_back
				(
					vkInit::to_descriptor_type(binding["descriptor_type"]),
					vkUtil::to_shader_stage(binding["stage_flags"]),
					binding["descriptor_count"].get<uint32_t>(),
					binding["binding"].get<uint32_t>()

				);
			}

		}
		descriptorSets.push_back(std::move(descriptorSet));
	}

	std::vector<vkInit::DescriptorSetBindings> layoutBindings;
	for (const auto& layouts : decriptorSet["layouts"])
	{
		vkInit::DescriptorSetBindings layoutBinding;
		for (const auto& layout : layouts["bindings"])
		{
			if (layout["stage_flags"].is_array())
			{
				std::vector<vkUtil::ShaderStage> stages;
				for (const auto& stage : layout["stage_flags"])
				{
					stages.emplace_back(vkUtil::to_shader_stage(stage.get<std::string_view>()));
				}
				layoutBinding.emplace_back
				(
					vkInit::to_descriptor_type(layout["descriptor_type"]),
					stages,
					layout["descriptor_count"].get<uint32_t>(),
					layout["binding"].get<uint32_t>()
					//layout["buffer"].get<uint16_t>()
				);
			}
			else
			{
				layoutBinding.emplace_back
				(
					vkInit::to_descriptor_type(layout["descriptor_type"]),
					vkUtil::to_shader_stage(layout["stage_flags"]),
					layout["descriptor_count"].get<uint32_t>(),
					layout["binding"].get<uint32_t>()
				);
			}
		}			
		layoutBindings.push_back(std::move(layoutBinding));
	}
	

	std::vector<vkUtil::BufferInput> bufferInfo;
	for (const auto& info : decriptorSet["descriptor_buffers"])
	{
		bufferInfo.emplace_back
		(
			info["size_max"].get<uint32_t>(),
			vkInit::to_buffer_type(info["type"].get<std::string_view>())
		);
	}

	tools::DescriptorSetRegistry::get_instance().intialize(descriptorSets, layoutBindings, bufferInfo);


	JsonReader pushConst(_jsonPushCosntantsFilePath);

	std::vector<vkType::PushConst> pushConsts;

	uint32_t offset = 0;
	for (const auto& push : pushConst["push_consts"])
	{
		pushConsts.emplace_back
		(
			push["size"].get<uint32_t>(),
			offset,
			vkUtil::enum_to_vk(vkUtil::to_shader_stage(push["shader"].get<std::string_view>()))
			
		);

		offset += push["size"].get<uint32_t>();
	}

	tools::PushConstRegistery::get_instance().initalize(pushConsts);
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

	spesifications.vertShaderPath = _shaderVertPath;
	spesifications.fragShaderPath = _shaderFragPath;
	spesifications.LogicalDevice =   _vkLogicalDevice;
	spesifications.swapchainExtent = _vkSwapchainExtent;
	spesifications.swapchainFormat = _vkSwapchainFormat;
	spesifications.swapchainFormat = _vkSwapchainFormat;
	spesifications.descriptorSetLayouts = _vkDescriptorSetLayouts;
	spesifications.pushConsts = _vkPushConsts;
	spesifications.instanced = false; 


	vkInit::GraphicsPipelineOutBundle output = vkInit::create_pipeline(spesifications, _debugMode);


	_vkPipeline = output.pipeline;

	_vkPipelineLayout = output.pipelineLayout;
	_vkRenderpass = output.renderpass;

}

std::vector <std::shared_ptr< vkInit::DescriptorBuffer >> BaseEngine::initalize_descriptor_buffers(const std::vector<vkUtil::BufferInput>& descriptorBuffer)
{
	std::vector<std::shared_ptr<vkInit::DescriptorBuffer>> buffer;

	buffer.emplace_back(std::make_shared<vkInit::DescriptorBufferData<Matrices>>(descriptorBuffer[SIZET(Buffer1)], _MVPMats));

	return buffer;
}


void BaseEngine::make_descriptor_sets()
{

	tools::DescriptorSetRegistry& descReg = tools::DescriptorSetRegistry::get_instance();
	const std::vector<vkInit::DescriptorSetBindings>& allDescriptorSets = descReg.get_descriptor_sets();

	size_t count = 0;
	for (const auto& size : descReg.get_descriptor_buffers())
	{
		count += size.size; 
	}

	std::cout << "Count: " << descReg.get_descriptor_set_layouts().size() << std::endl;

	vkInit::DescriptorSetOutBundle out = vkInit::create_descriptor_set(
		_vkLogicalDevice,
		_vkPhysicalDevice,
		allDescriptorSets,
		descReg.get_descriptor_set_layouts(),
		initalize_descriptor_buffers(descReg.get_descriptor_buffers()),
		_debugMode
	);
	
	if (out.descriptorSets.size() != SIZET(SetCount))
	{
		throw std::runtime_error("Descriptor Set Count does not match the Set Count! Set Count Enum must be update it!");
	}
	std::move(out.descriptorSets.begin(), out.descriptorSets.end(), _vkDescriptorSets.sets.begin());


	if (out.descriptorSetBuffers.size() != SIZET(BufferCount))
	{
		throw std::runtime_error("Descriptor Set Buffer Count does not match the Set Count! Buffer Count Enum must be update it!");
	}
	std::move(out.descriptorSetBuffers.begin(), out.descriptorSetBuffers.end(), _vkDescriptorSetBuffers.begin());

	for (size_t i = 0; i < allDescriptorSets.size(); i++)
	{
		_vkDescriptorSets.updated[i].reserve(allDescriptorSets[i].size());
		for (const auto& [j, set] : allDescriptorSets[i] | std::views::enumerate)
		{
			_vkDescriptorSets.updated[i].emplace_back(gen_desc_id(set.type), true);
		} 

	}

	_vkDescriptorPool = out.pool;

	_vkDescriptorSetLayouts = out.descriptorSetLayouts;

}

void BaseEngine::make_push_consts()
{
	tools::PushConstRegistery& pushReg = tools::PushConstRegistery::get_instance();
	_vkPushConsts = pushReg.get_push_consts();
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

	renderPassBeginInfo.clearValueCount = 1;

	renderPassBeginInfo.pClearValues = &UserInput::clear_color;

	commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);

	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, _vkPipeline);

	vk::Viewport vkViewport = vk::Viewport(0.0f, 0.0f, static_cast<float>(_window.GetBufferWidth()), static_cast<float>(_window.GetBufferHeight()), 0.0f, 1.0f);
	commandBuffer.setViewport(0, vkViewport);

	vk::Rect2D vkScissor = vk::Rect2D({ 0, 0 }, { static_cast<uint32_t>(_window.GetBufferWidth()), static_cast<uint32_t>(_window.GetBufferHeight()) }); 
	commandBuffer.setScissor(0, vkScissor);


	update_sets(commandBuffer);

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


void BaseEngine::handle_threads()
{

}

uint32_t BaseEngine::gen_desc_id(vk::DescriptorType desc)
{
	uint32_t id = 0;
	switch (desc)
	{
	case vk::DescriptorType::eUniformBuffer:
	{
		static uint32_t val = 0;
		id += 0 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eUniformBufferDynamic:
	{
		static uint32_t val = 0;
		id += 1000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eStorageBuffer:
	{
		static uint32_t val = 0;
		id += 2000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eStorageBufferDynamic:
	{
		static uint32_t val = 0;
		id += 3000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eUniformTexelBuffer:
	{
		static uint32_t val = 0;
		id += 4000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eStorageTexelBuffer:
	{
		static uint32_t val = 0;
		id += 5000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eStorageImage:
	{
		static uint32_t val = 0;
		id += 6000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eSampledImage:
	{
		static uint32_t val = 0;
		id += 0 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eSampler:
	{
		static uint32_t val = 0;
		id += 8000 + val;
		val++;
		break;
	}
	case vk::DescriptorType::eCombinedImageSampler:
	{
		static uint32_t val = 0;
		id += 9000 + val;
		val++;
		break;
	}
	default:
	{
		static uint32_t val = 0;
		id += 10000 + val;
		val++;
	}
	}
	return id;
}



void BaseEngine::camera_init(bool orthoOrPerpective)
{
	if (orthoOrPerpective)
	{
		tools::CameraBundleOrthographic bundle; 
		bundle.bottom = _window.GetBottomOrtho();
		bundle.left = _window.GetLeftOrtho();
		bundle.right = _window.GetWidth();
		bundle.top = _window.GetHeight();
		bundle.nearZ = 0.1f;
		bundle.farZ = 100.0f;
		bundle.speed = 0.5f;
		bundle.turnSpeed = 0.5f;
		bundle.position = glm::vec3(0.0f, 0.0f, 0.0f);
		bundle.startPYR = glm::vec3(0.0f, 0.0f, 0.0f);
		bundle.front = glm::vec3(0.0f, 0.0f, -1.0f);
		//bundle.direction = tools::Direction::Forward;
		_camera = std::move(tools::CameraT(bundle));
	}
	else
	{
		tools::CameraBundlePerspective bundle; 
		bundle.fov = 45.0f;
		bundle.aspectRatio = _window.GetAspectRatio();
		bundle.nearZ = 0.1f;
		bundle.farZ = 100.0f;
		bundle.speed = 0.5f;
		bundle.turnSpeed = 0.5f;
		bundle.position = glm::vec3(0.0f, 0.0f, 0.0f);
		bundle.startPYR = glm::vec3(0.0f, 0.0f, 0.0f);
		bundle.front = glm::vec3(0.0f, 0.0f, -1.0f);
		
		_camera = std::move(tools::CameraT(bundle)); 
	}
	_camera.set_commands_to_window(_window);

	_MVPMats._viewMat = _camera.get_view();
	_MVPMats._projMat = _camera.get_projection();
	_MVPMats._modelMat = glm::mat4(1.0f);

}



void BaseEngine::render()
{
	_deltaTime = _timer.get_delta_time(false);

	update_FPS();
	
	_window.pollEvents();

	game_logic(_deltaTime);

	check_vk_result(_vkLogicalDevice.waitForFences(1, &_vkSwapchainFrames[_frameNum].vkFenceInFlight, VK_TRUE, UINT64_MAX));


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
		std::cout << "Swapchain OUT OF DATE: " << err.what() << "\n";
		return;
	}
	catch (vk::IncompatibleDisplayKHRError& err) 
	{
		std::cout << "Remakeing Swapchain: " << err.what() << "\n";
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

	_vkLogicalDevice.waitIdle();

	destroy_swapchain();

	_vkLogicalDevice.destroyCommandPool(_vkCommandPool);

	_vkLogicalDevice.destroyDescriptorPool(_vkDescriptorPool);

	for (const auto& layout : _vkDescriptorSetLayouts)
	{
		_vkLogicalDevice.destroyDescriptorSetLayout(layout);
	}

	_vkLogicalDevice.destroyPipeline(_vkPipeline);

	_vkLogicalDevice.destroyPipelineLayout(_vkPipelineLayout);

	_vkLogicalDevice.destroyRenderPass(_vkRenderpass);

	for (const auto& item : _vkDescriptorSetBuffers)
	{
		vkUtil::destroy_vk_util_buffer(_vkLogicalDevice, item);
	}

	_instance.destroySurfaceKHR(_vkPresentSurface);

	if (_debugMode)
	{
		_instance.destroyDebugUtilsMessengerEXT(_debugMessenger, nullptr, _dldi);
	}


	_vkLogicalDevice.destroy();

	_instance.destroy();

	glfwTerminate();
}

