#pragma once

#include "config.h" 
#include <filesystem>

#include "vkUtil\include\vertex.h" 

namespace vkInit
{


	struct BaseGraphicsPipelineInBundle
	{
		vk::Device LogicalDevice;

		std::filesystem::path vertShaderPath;
		std::filesystem::path fragShaderPath;

		vk::Format swapchainFormat;
		vk::Extent2D swapchainExtent;
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts; 
	};

	template <vkType::VertBuff T>
	struct GraphicsPipelineInBundleT;

	template <>
	struct GraphicsPipelineInBundleT<AllInOneVertBuffer> : BaseGraphicsPipelineInBundle
	{
		bool instanced;
	};

	template <>
	struct GraphicsPipelineInBundleT<OncePerVertBuffer> : BaseGraphicsPipelineInBundle
	{
		std::array<bool, vkType::Vert::size()> instanced;
	};

	using GraphicsPipelineInBundle = GraphicsPipelineInBundleT<UserInput::AttributeDescription>;


	struct GraphicsPipelineOutBundle
	{
		vk::RenderPass renderpass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;

	};

} // namespace vkInit