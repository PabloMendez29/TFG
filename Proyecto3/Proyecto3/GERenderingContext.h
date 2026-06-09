#pragma once
#include "GERenderingContext.h"

#include <vulkan/vulkan.h>
#include <iostream>
#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GEPipelineConfig.h"
#include "GEDepthBuffer.h"

//
// CLASE: GERenderingContext
//
// DESCRIPCIÓN: Clase que describe un contexto de renderizado
//
class GERenderingContext
{
public:
	uint32_t imageCount;

private:
	uint32_t pipelineIndex;
	VkFormat format;
	VkExtent2D extent;
	VkRenderPass renderPass;
	std::vector<VkPipeline> graphicsPipeline;
	std::vector<VkDescriptorSetLayout> descriptorSetLayout;
	std::vector<VkPipelineLayout> pipelineLayout;
	std::vector<GEDepthBuffer*> depthBuffers;
	std::vector<VkFramebuffer> framebuffers;
	VkViewport viewport;
	VkRect2D scissor;

public:
	GERenderingContext(GEGraphicsContext* gc, GEDrawingContext* dc, GEPipelineConfig* config);
	void destroy(GEGraphicsContext* gc);
	void addGraphicsPipeline(GEGraphicsContext* gc, GEPipelineConfig* config);
	void setActivePipeline(uint32_t index);
	VkDescriptorSetLayout getActiveDescriptorSetLayout();
	VkPipelineLayout getActivePipelineLayout();
	void insertBeginCommands(std::vector<VkCommandBuffer> commandBuffers);
	void insertEndCommands(std::vector<VkCommandBuffer> commandBuffers);
	void insertPipelineCommands(std::vector<VkCommandBuffer> commandBuffers);

private:
	// Métodos de creación de componentes
	void createRenderPass(GEGraphicsContext* gc);
	void createGraphicsPipeline(GEGraphicsContext* gc, GEPipelineConfig* config);
	void createDepthBuffers(GEGraphicsContext* gc);
	void createFramebuffers(GEGraphicsContext* gc, GEDrawingContext* dc);

	// Métodos de definición del pipeline de renderizado
	void createPipelineLayout(GEGraphicsContext* gc, GEPipelineConfig* config);
	void createVertexShaderStageCreateInfo(GEGraphicsContext* gc, int resource, VkShaderModule* vertShaderModule, VkPipelineShaderStageCreateInfo* vertShaderStageInfo);
	void createFragmentShaderStageCreateInfo(GEGraphicsContext* gc, int resource, VkShaderModule* fragShaderModule, VkPipelineShaderStageCreateInfo* fragShaderStageInfo);
	void createPipelineVertexInputStateCreateInfo(GEPipelineConfig* config, VkPipelineVertexInputStateCreateInfo* vertexInputInfo);
	void createPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo* inputAssembly);
	void createPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo* viewportState);
	void createPipelineRasterizationStateCreateInfo(GEPipelineConfig* config, VkPipelineRasterizationStateCreateInfo* rasterizer);
	void createPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo* multisampling);
	void createPipelineDepthStencilStateCreateInfo(GEPipelineConfig* config, VkPipelineDepthStencilStateCreateInfo* depthStencil);
	void createPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlending);

	// Métodos auxiliares
	VkShaderModule createShaderModule(GEGraphicsContext* gc, const std::vector<char>& code);
	std::vector<char> getFileFromResource(int resource);
};

