#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"

#include "GEVertexAnimated.h"
#include "GETransform.h"
#include "GELight.h"
#include "GEMaterial.h"

#include "GEIndexBuffer.h"
#include "GEVertexBuffer.h"
#include "GEUniformBuffer.h"

#include "GETexture.h"
#include <glm/glm.hpp>
#include <vector>
#include "GEStorageBuffer.h"
#include "GEDescriptorSet.h"

	//
	// CLASE: GEPiece
	//
	// DESCRIPCIÓN: Clases que representa una pieza
	//
class GEPiece
{
public:
	void initialize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs);
	void finalize(GEGraphicsContext* gc);
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 location, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs);
	void setLight(GELight l);
	void setMaterial(GEMaterial m);
	void setTexture(GETexture* texture);

protected:
	std::vector<GEVertexAnimated> vertices;
	std::vector<uint16_t> indices;
	std::vector<glm::mat4> matrices;

	GELight light;
	GEMaterial material;
	GETexture* texture;

private:
	GEVertexBuffer* vbo;
	GEIndexBuffer* ibo;
	GEUniformBuffer* transformBuffer;
	GEUniformBuffer* materialBuffer;
	GEUniformBuffer* lightBuffer;
	GEStorageBuffer* jointMatrixBuffer;
	GEDescriptorSet* dset;

};
