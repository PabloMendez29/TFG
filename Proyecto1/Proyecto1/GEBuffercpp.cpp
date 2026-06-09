#include "GEBuffer.h"


//
// FUNCIÓN:  GEUniformBuffer::update(GEGraphicsContext* gc, uint32_t currentImage, size_t size, const void* data)
//
// PROPÓSITO: Actualiza el valor almacenado en un Uniform Buffer
//
void GEBuffer::update(GEGraphicsContext* gc, uint32_t currentImage, size_t size, const void* data)
{
	void* mdata;
	vkMapMemory(gc->device, memories[currentImage], 0, size, 0, &mdata);
	memcpy(mdata, data, size);
	vkUnmapMemory(gc->device, memories[currentImage]);
}

//
// FUNCIÓN:  GEUniformBuffer::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Destruye los campos de un Uniform Buffer
//
void GEBuffer::destroy(GEGraphicsContext* gc)
{
	uint32_t size = (uint32_t)buffers.size();
	for (uint32_t i = 0; i < size; i++)
	{
		vkDestroyBuffer(gc->device, buffers[i], nullptr);
		vkFreeMemory(gc->device, memories[i], nullptr);
	}
}
