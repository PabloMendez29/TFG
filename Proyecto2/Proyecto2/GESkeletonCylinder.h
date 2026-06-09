#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GEBalljoint.h"
#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GELight.h"
#include "GESkeleton.h"

//
// CLASE: GESkeletonCylinder
//
// DESCRIPCIÓN: Clase hija de GESkeleton que representa el esqueleto de un cilindro
//
class GESkeletonCylinder : public GESkeleton
{
public:
	GERenderingContext* rc;
	GEGraphicsContext* gc;

	GEBalljoint* vertebra1;
	GEBalljoint* vertebra2;


	GESkeletonCylinder(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light);
	void setPose(std::vector<glm::vec3> pose);
};
