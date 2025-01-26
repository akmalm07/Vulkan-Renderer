#pragma once 

#include "config.h"

#include "vkUtil\include\render_structs.h"
#include "vkInit\include\discription.h"




namespace vkInit {

	//struct PushConstentsOutJSON
	//{
	//	vk::ShaderStageFlagBits shader;
	//	uint32_t offset;
	//};

	struct GraphicsPipelineInBundle
	{
		vk::Device LogicalDevice;

		std::filesystem::path vertShaderPath;
		std::filesystem::path fragShaderPath;

		vk::Format swapchainFormat;
		vk::Extent2D swapchainExtent;
	};
	
	struct GraphicsPipelineOutBundle
	{
		vk::RenderPass renderpass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;

	};


	std::vector<vk::PushConstantRange> evaluate_push_constants(const std::vector<vkType::PushConst>& pushConsts, bool debug);

	vk::PushConstantRange create_push_constant(uint32_t offset, uint32_t size, vk::ShaderStageFlagBits shader, bool debug);

	GraphicsPipelineOutBundle create_pipeline(GraphicsPipelineInBundle& spesifications, 
		std::vector<vkDiscription::DiscriptorBundle>& discriptorSet, const std::vector<vkType::PushConst>& pushConsts, bool debug);
	
	vk::PipelineLayout create_pipeline_layout(vk::Device& logicalDevice, const std::vector<vkType::PushConst>& pushs, bool debug);

	vk::RenderPass create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug);



}
