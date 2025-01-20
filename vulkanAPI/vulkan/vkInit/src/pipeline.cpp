#include "pch.h"

#include "vkInit\include\pipeline.h"
#include "vkUtil\include\shader.h"

vk::PushConstantRange vkInit::create_push_constant(size_t offset, size_t size, vk::ShaderStageFlagBits shader, bool debug)
{
    vk::PushConstantRange pushConstantInfo = {};

    pushConstantInfo.offset = offset;

    pushConstantInfo.size = size;

    pushConstantInfo.stageFlags = shader;

    return pushConstantInfo;

}

vkInit::GraphicsPipelineOutBundle vkInit::create_pipeline(GraphicsPipelineInBundle& spesifications, 
    std::vector<vkDiscription::DiscriptorBundle>& discriptorSet, bool debug)
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

   
    std::vector<vk::VertexInputAttributeDescription> bindingAttributes = {};

    vk::VertexInputBindingDescription bindingDescription = {};


    uint32_t numOfDescriptors = 0;
    uint32_t numOfAttrib = 0;

    for (size_t i = 0; i < discriptorSet.size(); i++)
    {
        uint32_t totalOffset = vkVert::enumerate_pos_stride(discriptorSet[i].stride.pos)  + 
                               vkVert::enumerate_color_stride(discriptorSet[i].stride.col) + 
                               vkVert::enumerate_tex_stride(discriptorSet[i].stride.tex)   + 
                               vkVert::enumerate_normal_stride(discriptorSet[i].stride.norm);


        bindingAttributes = vkDiscription::get_attribute_descriptions(discriptorSet[i].stride, i, debug); 

        bindingDescription = vkDiscription::get_binding_description(totalOffset * sizeof(float), i, discriptorSet[i].isPerInstanceRate);

        numOfAttrib = numOfAttrib + bindingAttributes.size();


        numOfDescriptors++;
    }
    vertexInputInfo.vertexAttributeDescriptionCount = numOfAttrib;

    vertexInputInfo.pVertexAttributeDescriptions = bindingAttributes.data();


    vertexInputInfo.vertexBindingDescriptionCount = numOfDescriptors;

    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;


    vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();

    pipelineCreateInfo.pVertexInputState = &vertexInputInfo;


    vk::PipelineInputAssemblyStateCreateInfo inputAssemblyInfo = {};

    inputAssemblyInfo.flags = vk::PipelineInputAssemblyStateCreateFlags();

    inputAssemblyInfo.topology = vk::PrimitiveTopology::eTriangleList;

    pipelineCreateInfo.pInputAssemblyState = &inputAssemblyInfo;

    //vertex shader

    vk::PipelineShaderStageCreateInfo vertShaderInfo = {};

    vk::ShaderModule vertShader = vkInit::create_shader_module(spesifications.vertShaderPath, spesifications.LogicalDevice, debug);

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
    
    viewport.width = spesifications.swapchainExtent.width;

    viewport.height = spesifications.swapchainExtent.height;
    
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

    rastInfo.cullMode = vk::CullModeFlagBits::eBack;
    
    rastInfo.frontFace = vk::FrontFace::eClockwise;
    
    rastInfo.depthBiasEnable = VK_FALSE;

    
    pipelineCreateInfo.pRasterizationState = &rastInfo;


    //fragment shader

    vk::PipelineShaderStageCreateInfo fragShaderInfo = {};

    vk::ShaderModule fragShader = vkInit::create_shader_module(spesifications.fragShaderPath, spesifications.LogicalDevice, debug); 

    fragShaderInfo.stage = vk::ShaderStageFlagBits::eFragment;

    fragShaderInfo.pName = "main";

    fragShaderInfo.module = fragShader;

    shaderStages.push_back(fragShaderInfo); 


    pipelineCreateInfo.stageCount = shaderStages.size();
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
    

    vk::PipelineLayout pipelineLayout = create_pipeline_layout(spesifications.LogicalDevice, debug);
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



vk::PipelineLayout vkInit::create_pipeline_layout(vk::Device& logicalDevice, bool debug)
{
    if (debug)
    {
        std::cout << "Creating pipeline layout... \n";
    }
    vk::PipelineLayoutCreateInfo layoutInfo = {};
    
    layoutInfo.flags = vk::PipelineLayoutCreateFlags();

    layoutInfo.setLayoutCount = 0;
    
    layoutInfo.pushConstantRangeCount = 1;
    
    vk::PushConstantRange constantRangeInfo = create_push_constant(0, sizeof(vkUtil::ObjectData), vk::ShaderStageFlagBits::eVertex, debug);

    layoutInfo.pPushConstantRanges = &constantRangeInfo;


    
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

vk::RenderPass vkInit::create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug)
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
    
    colorAttachment.storeOp= vk::AttachmentStoreOp::eStore;

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
