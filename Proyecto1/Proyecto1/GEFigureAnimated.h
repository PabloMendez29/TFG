#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEVertexAnimated.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include "GETexture.h"
#include "GEVertexBuffer.h"
#include "GEIndexBuffer.h"
#include "GEUniformBuffer.h"
#include "GEStorageBuffer.h"
#include "GEDescriptorSet.h"
#include <glm/glm.hpp>
#include <vector>

//
// CLASE: GEFigureAnimated
//
// DESCRIPCIÓN: Clase que describe una figura formada por una malla de vértices
//
class GEFigureAnimated
{
protected:
	std::vector<GEVertexAnimated> vertices;
	std::vector<uint16_t> indices;
	glm::mat4 location;
	GEMaterial material;
	GELight light;
	GETexture* texture;

public:

	void initialize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs);
	void destroy(GEGraphicsContext* gc);
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs);

	void resetLocation();
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);

	void setLocation(glm::mat4 m);
	void setMaterial(GEMaterial m);
	void setLight(GELight l);
	void setTexture(GETexture* t);

private:
	GEVertexBuffer* vbo;
	GEIndexBuffer* ibo;
	GEUniformBuffer* transformBuffer;
	GEUniformBuffer* materialBuffer;
	GEUniformBuffer* lightBuffer;
	GEStorageBuffer* jointMatrixBuffer;
	GEDescriptorSet* dset;
};

