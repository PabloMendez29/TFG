#pragma once

#include <vulkan/vulkan.h>
#include <vector>

//
// CLASE: GEPipelineConfig
//
// PROPÓSITO: Almacena la configuración de un pipeline de renderizado
//
class GEPipelineConfig {
public:
	int vertex_shader;
	int fragment_shader;

	int attrStride;
	std::vector<VkFormat> attrFormats;
	std::vector<int> attrOffsets;

	std::vector<VkDescriptorType> descriptorTypes;
	std::vector<VkShaderStageFlags> descriptorStages;

	VkBool32 depthTestEnable;
	VkCullModeFlags cullMode;
	VkExtent2D extent;

	VkPolygonMode polygonMode;

	GEPipelineConfig();
};