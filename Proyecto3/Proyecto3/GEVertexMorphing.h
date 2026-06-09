#pragma once

#include <glm\glm.hpp>

//
// ESTRUCTURA: GEVertexMorphing
//
// DESCRIPCIÓN: Estructura que describe los atributos de un vértice
//
typedef struct
{
	glm::vec3 pos1;
	glm::vec3 norm1;
	glm::vec3 pos2;
	glm::vec3 norm2;
	glm::vec2 tex;
} GEVertexMorphing;
