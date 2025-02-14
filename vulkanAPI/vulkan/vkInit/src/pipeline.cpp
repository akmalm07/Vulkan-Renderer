#include "pch.h"

#include "vkInit\include\pipeline.h"
#include "vkInit\include\discription.h"
#include "vkUtil\include\vertex.h"
#include "vkUtil\include\shader.h"
#include "vkUtil\include\render_structs.h"
#include "tools\include\const_push_registry.h"


namespace vkInit
{
	std::vector<vk::PushConstantRange> evaluate_push_constants(const std::vector<vkType::PushConst>& pushConsts, bool debug)
	{

		std::vector<vk::PushConstantRange> pushConstants;

		for (const auto& push : pushConsts)
		{
			std::cout << "Push constant offset: " << push._offset << " size: " << push._size << " shader: " << UINT32(push._shader) << "\n";
			pushConstants.emplace_back(create_push_constant(push._offset, push._size, push._shader, debug));
		}

		return pushConstants;
	}

	vk::PushConstantRange create_push_constant(uint32_t offset, uint32_t size, vk::ShaderStageFlagBits shader, bool debug)
	{
		vk::PushConstantRange pushConstantInfo = {};

		pushConstantInfo.offset = offset;

		pushConstantInfo.size = size;

		pushConstantInfo.stageFlags = shader;

		return pushConstantInfo;

	}

	[[nodiscard]] GraphicsPipelineOutBundle create_pipeline(GraphicsPipelineInBundle& spesifications, bool debug)
	{

		if (debug)
		{
			std::cout << "Creating pipeline... \n";
		}


		vk::GraphicsPipelineCreateInfo pipelineCreateInfo = {};

		pipelineCreateInfo.flags = vk::PipelineCreateFlags();




		std::vector <vk::PipelineShaderStageCreateInfo> shaderStages;

		//vertex input 

		vk::PipelineVertexInputStateCreateInfo vertexInputInfo = {};



		auto discriptorsIn = vkDiscription::attrib_and_desc(spesifications.instanced, debug);
		{
			std::optional<vkDiscription::DescriptionOutBundle> in;
			std::optional<vkDiscription::DescriptionOutBundleSeperate> inSep;

			if constexpr (std::same_as<UserInput::AttributeDescription, AllInOneVertBuffer>)
			{
				in = std::get<vkDiscription::DescriptionOutBundle>(discriptorsIn);
			}
			else if constexpr (std::same_as<UserInput::AttributeDescription, OncePerVertBuffer>)
			{
				inSep = std::get<vkDiscription::DescriptionOutBundleSeperate>(discriptorsIn);
			}

			if (in.has_value())
			{
				vertexInputInfo.vertexBindingDescriptionCount = 1;
				vertexInputInfo.pVertexBindingDescriptions = &in->bindingDesc;
				vertexInputInfo.vertexAttributeDescriptionCount = UINT32(in->bindingAttrib.size());
				vertexInputInfo.pVertexAttributeDescriptions = in->bindingAttrib.data();
			}
			else if (inSep.has_value())
			{
				vertexInputInfo.vertexBindingDescriptionCount = UINT32(inSep->bindingDesc.size());
				vertexInputInfo.pVertexBindingDescriptions = inSep->bindingDesc.data();
				vertexInputInfo.vertexAttributeDescriptionCount = UINT32(inSep->bindingAttrib.size());
				vertexInputInfo.pVertexAttributeDescriptions = inSep->bindingAttrib.data();
			}
			else
			{
				std::cerr << "Error creating vertex input: " << "No discriptor bundle was created" << "\n";
				return {};
			}
		}
		vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();

		pipelineCreateInfo.pVertexInputState = &vertexInputInfo;


		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyInfo = {};

		inputAssemblyInfo.flags = vk::PipelineInputAssemblyStateCreateFlags();

		inputAssemblyInfo.topology = vk::PrimitiveTopology::eTriangleList;// ::eTriangleList 

		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyInfo;

		//vertex shader

		vk::PipelineShaderStageCreateInfo vertShaderInfo = {};

		vk::ShaderModule vertShader = create_shader_module(spesifications.vertShaderPath, spesifications.LogicalDevice, debug);

		vertShaderInfo.stage = vk::ShaderStageFlagBits::eVertex;

		vertShaderInfo.pName = "main";

		vertShaderInfo.module = vertShader;

		shaderStages.push_back(vertShaderInfo);

		//To make the scissor and viewport
		std::vector<vk::DynamicState> dynamicStates = {
		vk::DynamicState::eViewport,
		vk::DynamicState::eScissor
		};

		vk::PipelineDynamicStateCreateInfo dynamicStateCreateInfo({}, dynamicStates);

		pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;

		//viewport and scissor

		vk::Viewport viewport = {};

		viewport.x = 0.0f;

		viewport.y = 0.0f;

		viewport.width = UINT32(spesifications.swapchainExtent.width);

		viewport.height = UINT32(spesifications.swapchainExtent.height);

		viewport.maxDepth = 1.0f;
		viewport.minDepth = 0.0f;

		vk::Rect2D scissor = {};

		scissor.offset.x = 0.0;
		scissor.offset.y = 0.0f;

		scissor.extent = spesifications.swapchainExtent;

		vk::PipelineViewportStateCreateInfo viewportInfo = {};

		viewportInfo.flags = vk::PipelineViewportStateCreateFlags();

		viewportInfo.viewportCount = 1;

		viewportInfo.scissorCount = 1;

		viewportInfo.pViewports = &viewport;

		viewportInfo.pScissors = &scissor;


		pipelineCreateInfo.pViewportState = &viewportInfo;


		//Rasteurizer state

		vk::PipelineRasterizationStateCreateInfo rastInfo = {};

		rastInfo.flags = vk::PipelineRasterizationStateCreateFlags();

		rastInfo.depthClampEnable = VK_FALSE;

		rastInfo.rasterizerDiscardEnable = VK_FALSE;

		rastInfo.rasterizerDiscardEnable = VK_FALSE;

		rastInfo.polygonMode = vk::PolygonMode::eFill;

		rastInfo.lineWidth = 1.0f;

		rastInfo.cullMode = vk::CullModeFlagBits::eBack; // ::eBack 

		rastInfo.frontFace = vk::FrontFace::eClockwise;

		rastInfo.depthBiasEnable = VK_FALSE;


		pipelineCreateInfo.pRasterizationState = &rastInfo;


		//fragment shader

		vk::PipelineShaderStageCreateInfo fragShaderInfo = {};

		vk::ShaderModule fragShader = create_shader_module(spesifications.fragShaderPath, spesifications.LogicalDevice, debug);

		fragShaderInfo.stage = vk::ShaderStageFlagBits::eFragment;

		fragShaderInfo.pName = "main";

		fragShaderInfo.module = fragShader;

		shaderStages.push_back(fragShaderInfo);


		pipelineCreateInfo.stageCount = UINT32(shaderStages.size());
		pipelineCreateInfo.pStages = shaderStages.data();


		//Multisampling


		vk::PipelineMultisampleStateCreateInfo multisamplingInfo = {};

		multisamplingInfo.flags = vk::PipelineMultisampleStateCreateFlags();

		multisamplingInfo.sampleShadingEnable = VK_FALSE;

		multisamplingInfo.rasterizationSamples = vk::SampleCountFlagBits::e1;


		pipelineCreateInfo.pMultisampleState = &multisamplingInfo;


		vk::PipelineColorBlendAttachmentState colorBlendAttachment = {};

		colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachment.blendEnable = VK_FALSE;

		vk::PipelineColorBlendStateCreateInfo colorBlendInfo = {};

		colorBlendInfo.flags = vk::PipelineColorBlendStateCreateFlags();

		colorBlendInfo.logicOpEnable = VK_FALSE;

		colorBlendInfo.logicOp = vk::LogicOp::eCopy;

		colorBlendInfo.attachmentCount = 1;

		colorBlendInfo.pAttachments = &colorBlendAttachment;

		colorBlendInfo.blendConstants[0] = 0.0f;
		colorBlendInfo.blendConstants[1] = 0.0f;
		colorBlendInfo.blendConstants[2] = 0.0f;
		colorBlendInfo.blendConstants[3] = 0.0f;

		pipelineCreateInfo.pColorBlendState = &colorBlendInfo;


		vk::PipelineLayout pipelineLayout = create_pipeline_layout(spesifications.LogicalDevice, 
			spesifications.descriptorSetLayouts, 
			spesifications.pushConsts,
			debug);

		pipelineCreateInfo.layout = pipelineLayout;


		vk::RenderPass renderPass = create_render_pass(spesifications.LogicalDevice, spesifications.swapchainFormat, debug);
		pipelineCreateInfo.renderPass = renderPass;

		pipelineCreateInfo.basePipelineHandle = nullptr;



		//Creating Pipeline

		vk::Pipeline pipeline = nullptr;

		try
		{
			vk::ResultValue<vk::Pipeline> result = spesifications.LogicalDevice.createGraphicsPipeline(nullptr, pipelineCreateInfo);
			if (result.result == vk::Result::eSuccess)
			{
				pipeline = result.value;
			}
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "Error creating pipeline: " << err.what() << "\n";
		}



		GraphicsPipelineOutBundle output = {};

		output.renderpass = renderPass;
		output.pipelineLayout = pipelineLayout;
		output.pipeline = pipeline;





		spesifications.LogicalDevice.destroyShaderModule(vertShader);
		spesifications.LogicalDevice.destroyShaderModule(fragShader);



		return output;
	}



	vk::PipelineLayout create_pipeline_layout(vk::Device& logicalDevice, const std::vector<vk::DescriptorSetLayout>& layouts,
		const std::vector<vkType::PushConst>& pushs, bool debug)
	{

		if (debug)
		{
			std::cout << "Creating pipeline layout... \n";
		}
		vk::PipelineLayoutCreateInfo layoutInfo = {};

		layoutInfo.flags = vk::PipelineLayoutCreateFlags();

		layoutInfo.setLayoutCount = 0;

		std::vector<vk::PushConstantRange> pushConsts = evaluate_push_constants(pushs, debug);

		layoutInfo.pushConstantRangeCount = UINT32(pushConsts.size());

		layoutInfo.pPushConstantRanges = pushConsts.data();

		layoutInfo.setLayoutCount = UINT32(layouts.size());

		layoutInfo.pSetLayouts = layouts.data();


		try
		{
			return logicalDevice.createPipelineLayout(layoutInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "Error creating the pipeline layout: " << err.what() << "\n";
			return nullptr;
		}


		return nullptr;
	}

	vk::RenderPass create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug)
	{

		if (debug)
		{
			std::cout << "Creating renderpass... \n";
		}

		vk::AttachmentDescription colorAttachment = {};

		colorAttachment.flags = vk::AttachmentDescriptionFlags();

		colorAttachment.format = format;

		colorAttachment.samples = vk::SampleCountFlagBits::e1;

		colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;

		colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;

		colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;

		colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;

		colorAttachment.initialLayout = vk::ImageLayout::eUndefined;

		colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;


		vk::AttachmentReference attachmentRef = {};

		attachmentRef.attachment = 0;

		attachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

		vk::SubpassDescription subpass = {};

		subpass.flags = vk::SubpassDescriptionFlags();

		subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;

		subpass.colorAttachmentCount = 1;

		subpass.pColorAttachments = &attachmentRef;





		vk::RenderPassCreateInfo renderPassCreateInfo = {};

		renderPassCreateInfo.flags = vk::RenderPassCreateFlags();

		renderPassCreateInfo.attachmentCount = 1;

		renderPassCreateInfo.pAttachments = &colorAttachment;

		renderPassCreateInfo.subpassCount = 1;

		renderPassCreateInfo.pSubpasses = &subpass;

		try
		{
			return logicalDevice.createRenderPass(renderPassCreateInfo);
		}
		catch (vk::SystemError& err)
		{
			std::cerr << "Error creating Renderpass: " << err.what() << "\n";
			return nullptr;
		}



		return nullptr;
	}

} // namespace vkInit