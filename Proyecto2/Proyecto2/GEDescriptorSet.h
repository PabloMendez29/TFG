#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEBuffer.h"
#include "GETexture.h"

//
// CLASE: GEDescriptorSet
//
// DESCRIPCIÓN: Clase que describe un conjunto de descriptores 
//
class GEDescriptorSet
{
private:
	VkDescriptorPool descriptorPool;

public:
	std::vector<VkDescriptorSet> descriptorSets;

public:

	GEDescriptorSet(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<GEBuffer*> ubos);
	GEDescriptorSet(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<GEBuffer*> ubos, std::vector<GETexture*> tex);
	void destroy(GEGraphicsContext* gc);
};

