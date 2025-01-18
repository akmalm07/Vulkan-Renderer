#pragma once 

#include "pch.h"

#include "vkInit\include\discription.h"

#include "vkUtil\include\render_structs.h"
#include <discription.h>



namespace vkInit {

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


	vk::PushConstantRange create_push_constant(size_t offset, size_t size, vk::ShaderStageFlagBits shader, bool debug);

	GraphicsPipelineOutBundle create_pipeline(GraphicsPipelineInBundle& spesifications, 
		std::vector<vkDiscription::DiscriptorBundle>& discriptorSet, bool debug);
	
	vk::PipelineLayout create_pipeline_layout(vk::Device& logicalDevice, bool debug);

	vk::RenderPass create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug);



}
