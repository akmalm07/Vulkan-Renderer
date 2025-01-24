#pragma once 

#include "pch.h"

#include "vkInit\include\discription.h"

#include "vkUtil\include\render_structs.h"
#include <discription.h>



namespace vkInit {

	struct PushConstentsOutJSON
	{
		vk::ShaderStageFlagBits shader;
		size_t offset;
	};

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

	std::vector<PushConstentsOutJSON> read_json_push_constants(const std::filesystem::path& path);

	vk::PushConstantRange create_push_constant(size_t offset, size_t size, vk::ShaderStageFlagBits shader, bool debug);

	GraphicsPipelineOutBundle create_pipeline(GraphicsPipelineInBundle& spesifications, 
		std::vector<vkDiscription::DiscriptorBundle>& discriptorSet, std::filesystem::path jsonpath, bool debug);
	
	vk::PipelineLayout create_pipeline_layout(vk::Device& logicalDevice, std::filesystem::path json, bool debug);

	vk::RenderPass create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug);



}
