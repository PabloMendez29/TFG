#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "GEBalljoint.h"
#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GELight.h"


//
// CLASE: GESkeleton
//
// DESCRIPCIÓN: Representa el esqueleto o rig
//
class GESkeleton
{
public:
	glm::mat4 matrizCuerpo;
	std::vector<GEBalljoint*> hijos;

private:
	glm::vec3 location;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 dir;
	
	GERenderingContext* rc;
	GEGraphicsContext* gc;

public:
	GESkeleton(glm::vec3 offset, glm::vec3 right, glm::vec3 up,	GEGraphicsContext* gc, GERenderingContext* rc, GELight light);
	~GESkeleton();
	void destroy(GEGraphicsContext* gc);

	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nRight, glm::vec3 nUp);

	void translate(glm::vec3 t);
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection);
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
	virtual void setPose(std::vector<glm::vec3> pose) = 0;

	void computeBindingMatrixs();
	std::vector<glm::mat4> getJointMatrixs();

	void computeMatrix();
};

