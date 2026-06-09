#pragma once

#include <vulkan/vulkan.h>
#include "GEGraphicsContext.h"
#include "GEBuffer.h"
#include <vector>

//
// CLASE: GEStorageBuffer
//
// DESCRIPCIÓN: Clase que describe un conjunto de buffers para almacenar variables de tamaño indefinido 
//
class GEStorageBuffer : public GEBuffer
{
public:
	GEStorageBuffer(GEGraphicsContext* gc, uint32_t imageCount, size_t bufferSize);
};
