#include "GEDescriptorSet.h"

#include "GEBuffer.h"
#include "GETexture.h"
#include <iostream>

//
// FUNCIÓN:GEDescriptorSet::GEDescriptorSet(GEGraphicsContext* gc, std::vector<GEUniformBuffer> ubos)
// 
// PROPÓSITO: Crea los conjuntos de descriptores asociados a los buffers
//
GEDescriptorSet::GEDescriptorSet(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<GEBuffer*> ubos)
{
	
	uint32_t bufferCount = (uint32_t) ubos.size();
	uint32_t imageCount = rc->imageCount;

	std::vector<VkDescriptorPoolSize> poolSizes(bufferCount);

	for (uint32_t i = 0; i < bufferCount; i++)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = ubos[i]->tipo;
		poolSize.descriptorCount = imageCount;
		poolSizes[i] = poolSize;
	}

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = (uint32_t)poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = imageCount;

	if (vkCreateDescriptorPool(gc->device, &poolInfo, nullptr, &this->descriptorPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}

	std::vector<VkDescriptorSetLayout> layouts(imageCount, rc->getActiveDescriptorSetLayout());
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = this->descriptorPool;
	allocInfo.descriptorSetCount = imageCount;
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(imageCount);

	if (vkAllocateDescriptorSets(gc->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < imageCount; i++)
	{
		std::vector<VkDescriptorBufferInfo> buffersInfo;
		buffersInfo.resize(bufferCount);

		for (uint32_t j = 0; j < bufferCount; j++)
		{
			buffersInfo[j] = {};
			buffersInfo[j].buffer = ubos[j]->buffers[i];
			buffersInfo[j].offset = 0;
			buffersInfo[j].range = ubos[j]->bufferSize;
		}


		std::vector<VkWriteDescriptorSet> descriptorWrites;
		descriptorWrites.resize(bufferCount);

		for (int j = 0; j < bufferCount; j++) {
			descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[j].dstSet = this->descriptorSets[i];
			descriptorWrites[j].dstBinding = j;
			descriptorWrites[j].dstArrayElement = 0;
			descriptorWrites[j].descriptorType = ubos[j]->tipo;
			descriptorWrites[j].descriptorCount = 1;
			descriptorWrites[j].pBufferInfo = &buffersInfo[j];
		}

		vkUpdateDescriptorSets(gc->device, bufferCount, descriptorWrites.data(), 0, nullptr);
	}
}

//
// FUNCIÓN:GEDescriptorSet::GEDescriptorSet(GEGraphicsContext* gc, std::vector<GEUniformBuffer> ubos)
// 
// PROPÓSITO: Crea los conjuntos de descriptores asociados a los buffers
//
GEDescriptorSet::GEDescriptorSet(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<GEBuffer*> ubos, std::vector<GETexture*> tex)
{
	
	uint32_t bufferCount = (uint32_t)ubos.size();
	uint32_t textureCount = (uint32_t)tex.size();
	uint32_t imageCount = rc->imageCount;

	std::vector<VkDescriptorPoolSize> poolSizes(bufferCount + textureCount);

	for (uint32_t i = 0; i < bufferCount; i++)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = ubos[i]->tipo;
		poolSize.descriptorCount = imageCount;
		poolSizes[i] = poolSize;
	}
	for (uint32_t i = 0; i < textureCount; i++)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSize.descriptorCount = imageCount;
		poolSizes[bufferCount + i] = poolSize;
	}

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = (uint32_t)poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = imageCount;

	if (vkCreateDescriptorPool(gc->device, &poolInfo, nullptr, &this->descriptorPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}

	std::vector<VkDescriptorSetLayout> layouts(imageCount, rc->getActiveDescriptorSetLayout());
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = this->descriptorPool;
	allocInfo.descriptorSetCount = imageCount;
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(imageCount);

	if (vkAllocateDescriptorSets(gc->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < imageCount; i++)
	{
		std::vector<VkDescriptorBufferInfo> buffersInfo;
		buffersInfo.resize(bufferCount);

		for (uint32_t j = 0; j < bufferCount; j++)
		{
			buffersInfo[j] = {};
			buffersInfo[j].buffer = ubos[j]->buffers[i];
			buffersInfo[j].offset = 0;
			buffersInfo[j].range = ubos[j]->bufferSize;
		}

		std::vector<VkDescriptorImageInfo> imageInfo;
		imageInfo.resize(textureCount);

		for (uint32_t j = 0; j < textureCount; j++)
		{
			imageInfo[j] = {};
			imageInfo[j].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo[j].imageView = tex[j]->textureImageView;
			imageInfo[j].sampler = tex[j]->textureSampler;
		}

		std::vector<VkWriteDescriptorSet> descriptorWrites;
		descriptorWrites.resize(bufferCount + textureCount);

		for (int j = 0; j < bufferCount; j++) {
			descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[j].dstSet = this->descriptorSets[i];
			descriptorWrites[j].dstBinding = j;
			descriptorWrites[j].dstArrayElement = 0;
			descriptorWrites[j].descriptorType = ubos[j]->tipo;
			descriptorWrites[j].descriptorCount = 1;
			descriptorWrites[j].pBufferInfo = &buffersInfo[j];
		}
		
		for (int j = bufferCount; j < bufferCount + textureCount; j++) {
			descriptorWrites[j].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[j].dstSet = this->descriptorSets[i];
			descriptorWrites[j].dstBinding = j;
			descriptorWrites[j].dstArrayElement = 0;
			descriptorWrites[j].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;;
			descriptorWrites[j].descriptorCount = 1;
			descriptorWrites[j].pImageInfo = &imageInfo[j - bufferCount];
		}
		
		
		vkUpdateDescriptorSets(gc->device, bufferCount + textureCount, descriptorWrites.data(), 0, nullptr);
	}
}

//
// FUNCIÓN: GEDescriptorSet::destroy(GEGraphicsContext* gc) 
//
// PROPÓSITO: Destruye los conjuntos de descriptores
//
void GEDescriptorSet::destroy(GEGraphicsContext* gc) 
{
	vkFreeDescriptorSets(gc->device, descriptorPool, (uint32_t)descriptorSets.size(), descriptorSets.data());
	vkDestroyDescriptorPool(gc->device, descriptorPool, nullptr);
}
