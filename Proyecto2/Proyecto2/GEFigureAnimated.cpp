#include "GEFigureAnimated.h"

#include "GEVertexAnimated.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//
// FUNCIÓN: GEFigureAnimated::initialize(GEGraphicsContext* gc, GERenderingContext* rc)
//
// PROPÓSITO: Crea la figura
//
void GEFigureAnimated::initialize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs)
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

	location = glm::mat4(1.0f);

	
}

//
// FUNCIÓN: GEFigureAnimated::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Libera los buffers de la figura
//
void GEFigureAnimated::destroy(GEGraphicsContext* gc)
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
	delete texture;
}

//
// FUNCIÓN: GEFigureAnimated::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void GEFigureAnimated::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &(vbo->buffer), &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo->buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &(dset->descriptorSets[index]), 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: GEFigureAnimated::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void GEFigureAnimated::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs)
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
// FUNCIÓN: GEFigureAnimated::resetLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void GEFigureAnimated::resetLocation()
{
	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: GEFigureAnimated::setLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void GEFigureAnimated::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
}

//
// FUNCIÓN: GEFigureAnimated::translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento la matriz de localización (Model).
//
void GEFigureAnimated::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: GEFigureAnimated::rotate(float angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación la matriz de localización (Model).
//
void GEFigureAnimated::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: GEFigureAnimated::setMaterial(GEMaterial m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la figura
//
void GEFigureAnimated::setMaterial(GEMaterial m)
{
	this->material = m;
}

//
// FUNCIÓN: GEFigureAnimated::setLight(GELight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que ilumina la figura
//
void GEFigureAnimated::setLight(GELight l)
{
	this->light = l;
}


//
// FUNCIÓN: GEFigureAnimated::setLight(GELight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que ilumina la figura
//
void GEFigureAnimated::setTexture(GETexture* t)
{
	this->texture = t;
}
