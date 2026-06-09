#include "GESkeletonCylinder.h"

//
// FUNCIÓN: GESkeletonCylinder::GESkeletonCylinder(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light) : GESkeleton(offset, dir, up, gc, rc, light)
//
// PROPÓSITO: Contruye el esqueleto del cilindro
//
GESkeletonCylinder::GESkeletonCylinder(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light) : GESkeleton(offset, dir, up, gc, rc, light) {

    vertebra1 = new GEBalljoint(
        2.0f,
        glm::vec3(0.0f, 0.0f, -2.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    vertebra1->initialize(gc, rc, matrizCuerpo);
    vertebra1->setLight(light);
    hijos.push_back(vertebra1);

        vertebra2 = new GEBalljoint(
            2.0f,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        vertebra2->initialize(gc, rc, vertebra1->getMatriz());
        vertebra2->setLight(light);
        vertebra1->addHijo(vertebra2);

        

        computeMatrix();
}

//
// FUNCIÓN: GESkeletonCylinder::setPose(std::vector<glm::vec3> pose)
//
// PROPÓSITO: Asigna los angulos de euler a cada articulación
//
void GESkeletonCylinder::setPose(std::vector<glm::vec3> pose) {

    vertebra1->setPose(pose[0]);
    vertebra2->setPose(pose[1]);
}