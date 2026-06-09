#include "GEFigureMorphing.h"

#include "GEVertexMorphing.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//
// FUNCIÓN: GEFigureMorphing::initialize(GEGraphicsContext* gc, GERenderingContext* rc)
//
// PROPÓSITO: Crea la figura
//
void GEFigureMorphing::initialize(GEGraphicsContext* gc, GERenderingContext* rc)
{

	size_t vertexSize = sizeof(GEVertexMorphing) * vertices.size();
	vbo = new GEVertexBuffer(gc, vertexSize, vertices.data());

	size_t indexSize = sizeof(indices[0]) * indices.size();
	ibo = new GEIndexBuffer(gc, indexSize, indices.data());

	size_t transformBufferSize = sizeof(GETransform);
	transformBuffer = new GEUniformBuffer(gc, rc->imageCount, transformBufferSize);

	size_t materialBufferSize = sizeof(GEMaterial);
	materialBuffer = new GEUniformBuffer(gc, rc->imageCount, materialBufferSize);

	size_t lightBufferSize = sizeof(GELight);
	lightBuffer = new GEUniformBuffer(gc, rc->imageCount, lightBufferSize);

	size_t timeBufferSize = sizeof(float);
	timeBuffer = new GEUniformBuffer(gc, rc->imageCount, timeBufferSize);

	std::vector<GEBuffer*> ubos(4);
	ubos[0] = transformBuffer;
	ubos[1] = materialBuffer;
	ubos[2] = lightBuffer;
	ubos[3] = timeBuffer;

	std::vector<GETexture*> tex(2);
	tex[0] = texture1;
	tex[1] = texture2;

	dset = new GEDescriptorSet(gc, rc, ubos, tex);

	location = glm::mat4(1.0f);

	
}

//
// FUNCIÓN: GEFigureMorphing::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Libera los buffers de la figura
//
void GEFigureMorphing::destroy(GEGraphicsContext* gc)
{
	vbo->destroy(gc);
	ibo->destroy(gc);
	transformBuffer->destroy(gc);
	materialBuffer->destroy(gc);
	lightBuffer->destroy(gc);
	timeBuffer->destroy(gc);
	dset->destroy(gc);

	delete vbo;
	delete ibo;
	delete transformBuffer;
	delete materialBuffer;
	delete lightBuffer;
	delete timeBuffer;
	delete dset;
}

//
// FUNCIÓN: GEFigureMorphing::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void GEFigureMorphing::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &(vbo->buffer), &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo->buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &(dset->descriptorSets[index]), 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: GEFigureMorphing::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void GEFigureMorphing::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection, float tiempo)
{
	GETransform transform;
	transform.MVP = projection * view * location;
	transform.ModelViewMatrix = view * location;
	transform.ViewMatrix = view;

	transformBuffer->update(gc, index, sizeof(GETransform), &transform);
	materialBuffer->update(gc, index, sizeof(GEMaterial), &material);
	lightBuffer->update(gc, index, sizeof(GELight), &light);
	timeBuffer->update(gc, index, sizeof(float), &tiempo);

}

//
// FUNCIÓN: GEFigureMorphing::resetLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void GEFigureMorphing::resetLocation()
{
	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: GEFigureMorphing::setLocation(glm::mat4 m)
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void GEFigureMorphing::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
}

//
// FUNCIÓN: GEFigureMorphing::translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento la matriz de localización (Model).
//
void GEFigureMorphing::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: GEFigureMorphing::rotate(float angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación la matriz de localización (Model).
//
void GEFigureMorphing::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: GEFigureMorphing::setMaterial(GEMaterial m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la figura
//
void GEFigureMorphing::setMaterial(GEMaterial m)
{
	this->material = m;
}

//
// FUNCIÓN: GEFigureMorphing::setLight(GELight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que ilumina la figura
//
void GEFigureMorphing::setLight(GELight l)
{
	this->light = l;
}


//
// FUNCIÓN: GEFigureMorphing::setLight(GELight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que ilumina la figura
//
void GEFigureMorphing::setTextures(GETexture* t1, GETexture* t2)
{
	this->texture1 = t1;
	this->texture2 = t2;
}


