#include "GEStorageBuffer.h"

#include <iostream>

//
// FUNCIÓN: GEStorageBuffer::GEStorageBuffer(GEGraphicsContext* gc, size_t size, const void* data)
//
// PROPÓSITO:  Crea una lista de Storage Buffers asociados a cada imagen a generar
//
GEStorageBuffer::GEStorageBuffer(GEGraphicsContext* gc, uint32_t imageCount, size_t bufferSize)
{
	this->bufferSize = bufferSize;
	this->buffers.resize(imageCount);
	this->memories.resize(imageCount);
	this->tipo = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

	for (uint32_t i = 0; i < imageCount; i++)
	{
		VkBuffer buffer;
		VkDeviceMemory deviceMemory;

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = bufferSize;
		bufferInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(gc->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(gc->device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = gc->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(gc->device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate buffer memory!");
		}

		vkBindBufferMemory(gc->device, buffer, deviceMemory, 0);

		buffers[i] = buffer;
		memories[i] = deviceMemory;
	}
}



