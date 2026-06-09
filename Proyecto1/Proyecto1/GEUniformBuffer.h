#pragma once

#include "GEGraphicsContext.h"
#include "GEBuffer.h"
#include <vulkan/vulkan.h>
#include <vector>

//
// CLASE: GEUniformBuffer
//
// DESCRIPCIÓN: Clase que describe un conjunto de buffers para almacenar variables uniformes 
//
class GEUniformBuffer : public GEBuffer
{
public:
	GEUniformBuffer(GEGraphicsContext* gc, uint32_t imageCount, size_t bufferSize);
};

