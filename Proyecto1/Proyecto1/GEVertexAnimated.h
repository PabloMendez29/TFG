#pragma once

#include <glm\glm.hpp>

//
// ESTRUCTURA: GEVertexAnimated
//
// DESCRIPCIÓN: Estructura que describe los atributos de un vértice
//
typedef struct
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex;
	uint32_t ind; 

} GEVertexAnimated;