#pragma once

#include "GEGraphicsContext.h"
#include <vulkan/vulkan.h>
#include <vector>

//
// CLASE: GEBuffer
//
// DESCRIPCIÓN: 
//
class GEBuffer
{
public:
	size_t bufferSize;
	std::vector<VkBuffer> buffers;
	std::vector<VkDeviceMemory> memories;
	VkDescriptorType tipo;


	void update(GEGraphicsContext* gc, uint32_t currentImage, size_t size, const void* data);
	void destroy(GEGraphicsContext* gc);

	
};