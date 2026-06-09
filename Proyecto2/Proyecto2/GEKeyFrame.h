#pragma once
#include <vector>
#include <glm/vec3.hpp>


//
// ESTRUCTURA: Keyframe
//
// DESCRIPCIÓN: Estructura que almacena una pose junto a su duración
//
struct Keyframe {
	std::vector<glm::vec3> pose;
	float tiempo;
};
