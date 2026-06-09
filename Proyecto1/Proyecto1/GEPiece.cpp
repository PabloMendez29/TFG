#include "GEPiece.h"
#include "GEVertexAnimated.h"
#include "GETransform.h"
#include <glm/glm.hpp>

//
// FUNCIÓN: initialize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs)
//
// PROPÓSITO: Iniciliza la pieza creando su descriptor set
//
void GEPiece::initialize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs)
{
	size_t vertexSize = sizeof(GEVertexAnimated) * vertices.size();
	vbo = new GEVertexBuffer(gc, vertexSize, vertices.data());

	size_t indexSize = sizeof(indices[0]) * indices.size();
	ibo = new GEIndexBuffer(gc, indexSize, indices.data());

	size_t transformBufferSize = sizeof(GETransform);
	transformBuffer = new GEUniformBuffer(gc, rc->imageCount, transformBufferSize);

	size_t materialBufferSize = sizeof(GEMaterial);
	materialBuffer = new GEUniformBuffer(gc, rc->imageCount, materialBufferSize);

	size_t lightBufferSize = sizeof(GELight);
	lightBuffer = new GEUniformBuffer(gc, rc->imageCount, lightBufferSize);

	size_t jointMatrixBufferSize = sizeof(glm::mat4) * jointMatrixs.size();
	jointMatrixBuffer = new GEStorageBuffer(gc, rc->imageCount, jointMatrixBufferSize);

	std::vector<GEBuffer*> ubos(4);
	ubos[0] = transformBuffer;
	ubos[1] = materialBuffer;
	ubos[2] = lightBuffer;
	ubos[3] = jointMatrixBuffer;

	std::vector<GETexture*> tex(1);
	tex[0] = texture;

	dset = new GEDescriptorSet(gc, rc, ubos, tex);
}

//
// FUNCIÓN: GEPiece::finalize(GEGraphicsContext* gc)
//
// PROPÓSITO: Libera los buffers de la pieza
//
void GEPiece::finalize(GEGraphicsContext* gc)
{
	vbo->destroy(gc);
	ibo->destroy(gc);
	transformBuffer->destroy(gc);
	materialBuffer->destroy(gc);
	lightBuffer->destroy(gc);
	jointMatrixBuffer->destroy(gc);
	dset->destroy(gc);

	delete vbo;
	delete ibo;
	delete transformBuffer;
	delete materialBuffer;
	delete lightBuffer;
	delete jointMatrixBuffer;
	delete dset;

}

//
// FUNCIÓN: GEPiece::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void GEPiece::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &(vbo->buffer), &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo->buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &(dset->descriptorSets[index]), 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: GEPiece::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 location, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void GEPiece::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 location, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs)
{
	GETransform transform;
	transform.MVP = projection * view * location;
	transform.ModelViewMatrix = view * location;
	transform.ViewMatrix = view;

	transformBuffer->update(gc, index, sizeof(GETransform), &transform);
	materialBuffer->update(gc, index, sizeof(GEMaterial), &material);
	lightBuffer->update(gc, index, sizeof(GELight), &light);
	jointMatrixBuffer->update(gc, index, sizeof(glm::mat4) * jointMatrixs.size(), jointMatrixs.data());
}

//
// FUNCIÓN: GEPiece::setLight(Light l)
//
// PROPÓSITO: Asigna las propiedades de la luz que incide en la pieza
//
void GEPiece::setLight(GELight l)
{
	this->light = l;
}

//
// FUNCIÓN: GEPiece::setMaterial(Material m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la pieza
//
void GEPiece::setMaterial(GEMaterial m)
{
	this->material = m;
}

//
// FUNCIÓN: GEPiece::setTexture(Texture* tex)
//
// PROPÓSITO: Asigna la textura de la pieza
//
void GEPiece::setTexture(GETexture* tex)
{
	this->texture = tex;
}
