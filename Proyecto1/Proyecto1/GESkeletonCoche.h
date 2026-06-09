#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GEBalljoint.h"
#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GELight.h"
#include "GESkeleton.h"

//
// CLASE: GESkeletonCoche
//
// DESCRIPCIÓN: Clase hija de GESkeleton que representa el esqueleto de un coche
//
class GESkeletonCoche : public GESkeleton
{
public:
	GERenderingContext* rc;
	GEGraphicsContext* gc;

	GEBalljoint* principal;
	GEBalljoint* rueda1;
	GEBalljoint* rueda2;
	GEBalljoint* rueda3;
	GEBalljoint* rueda4;

	GESkeletonCoche(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light);
	void setPose(std::vector<glm::vec3> pose);
};
