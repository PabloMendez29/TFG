#include "GEListaPoses.h"
#include <vector>
#include <glm/vec3.hpp>

//
// FUNCIÓN: GEListaPoses::getKeyframes()
//
// PROPÓSITO: Devuelve un vector de keyframes
//
std::vector<Keyframe> GEListaPoses::getKeyframes() {
    return keyframes;
}

//
// FUNCIÓN: GEListaPoses::GEListaPoses()
//
// PROPÓSITO: Contruye todas las poses con la duracion de cada una
//
GEListaPoses::GEListaPoses() {

    
    std::vector<glm::vec3> pose1 = {
        glm::vec3(0.0f, 0.0f, 0.0f), // principal
        glm::vec3(0.0f, 0.0f, 0.0f), // rueda Alante Izq
    };

    keyframes.push_back({ pose1, 0.0f });

    std::vector<glm::vec3> pose2 = {
        glm::vec3(0.0f, 0.0f, 0.0f), // principal
        glm::vec3(45.0f, 0.0f, 0), // rueda Alante Izq
    };

    keyframes.push_back({ pose2, 5.0f });

    std::vector<glm::vec3> pose3 = {
        glm::vec3(0.0f, 0.0f, 0.0f), // principal
        glm::vec3(-45.0f, 0.0f, 0.0f), // rueda Alante Izq
    };

    keyframes.push_back({ pose3, 10.0f });

    std::vector<glm::vec3> pose4 = {
        glm::vec3(0.0f, 0.0f, 0.0f), // principal
        glm::vec3(0.0f, 0.0f, 0.0f), // rueda Alante Izq
    };

    keyframes.push_back({ pose4, 5.0f });

    
}

