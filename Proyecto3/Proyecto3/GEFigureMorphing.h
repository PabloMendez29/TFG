#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEVertexMorphing.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include "GETexture.h"
#include "GETime.h"
#include "GEVertexBuffer.h"
#include "GEIndexBuffer.h"
#include "GEUniformBuffer.h"
#include "GEStorageBuffer.h"
#include "GEDescriptorSet.h"
#include <glm/glm.hpp>
#include <vector>

//
// CLASE: GEFigureMorphing
//
// DESCRIPCIÓN: Clase que describe una figura formada por una malla de vértices capaz de hacer Morphing
//
class GEFigureMorphing
{
protected:
	std::vector<GEVertexMorphing> vertices;
	std::vector<uint16_t> indices;
	glm::mat4 location;
	GEMaterial material;
	GELight light;
	GETexture *texture1, *texture2;

public:

	void initialize(GEGraphicsContext* gc, GERenderingContext* rc);
	void destroy(GEGraphicsContext* gc);
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection, float time);
	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void setMaterial(GEMaterial m);
	void setLight(GELight l);
	void setTextures(GETexture* t1, GETexture* t2);


private:
	GEVertexBuffer* vbo;
	GEIndexBuffer* ibo;
	GEUniformBuffer* transformBuffer;
	GEUniformBuffer* materialBuffer;
	GEUniformBuffer* lightBuffer;
	GEUniformBuffer* timeBuffer;
	GEDescriptorSet* dset;

};

