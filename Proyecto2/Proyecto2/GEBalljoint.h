#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GESphere.h"
#include "GECylinder.h"
#include "GELight.h"
#include <glm\glm.hpp>

//
// CLASE: GEBalljoint
//
// DESCRIPCIÓN: Representa una articulación con 3 grados de libertad
// 
class GEBalljoint {
private:
	GLfloat length;
	glm::vec3 location;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat angles[3];
	GESphere* joint;
	GECylinder* bone;

public:
	std::vector<GEBalljoint*> hijos;
	glm::mat4 matrizPadre;
	GEBalljoint* padre = nullptr;
	glm::mat4 matrix;
	glm::mat4 bindingMatrix;

public:
	GEBalljoint(float l, glm::vec3 offset, glm::vec3 right, glm::vec3 up);
	void initialize(GEGraphicsContext* gc, GERenderingContext* rc, glm::mat4 parent);
	void destroy(GEGraphicsContext* gc);
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection);

	void setLight(GELight l);
	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
	void setPose(glm::vec3 pose);

	void ComputeMatrix(glm::mat4 parent);
	void computeBindingMatrix(glm::mat4 parent);

	glm::mat4 getMatriz();
	std::vector<GEBalljoint*> getHijos(); glm::mat4 getJointMatrix();
	void getJointMatrixs(std::vector<glm::mat4>& list);

	void addHijo(GEBalljoint* hijo);
};
