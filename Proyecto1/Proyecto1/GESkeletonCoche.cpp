#include "GESkeletonCoche.h"


//
// FUNCIÓN: GESkeletonCoche::GESkeletonCoche(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light) : GESkeleton(offset, dir, up, gc, rc, light)
//
// PROPÓSITO: Contruye el esqueleto del coche
//
GESkeletonCoche::GESkeletonCoche(glm::vec3 offset, glm::vec3 dir, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light) : GESkeleton(offset, dir, up, gc, rc, light) {

    principal = new GEBalljoint(
        2.0f,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    principal->initialize(gc, rc, matrizCuerpo);
    principal->setLight(light);
    hijos.push_back(principal);

        rueda1 = new GEBalljoint(
            1.0f,
            glm::vec3(2.0f, 0.0f, 2.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, -1.0f)
        );
        rueda1->initialize(gc, rc, principal->getMatriz());
        rueda1->setLight(light);
        principal->addHijo(rueda1);

        rueda2 = new GEBalljoint(
            1.0f,
            glm::vec3(2.0f, 0.0f, -5.4f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, -1.0f)
        );
        rueda2->initialize(gc, rc, principal->getMatriz());
        rueda2->setLight(light);
        principal->addHijo(rueda2);

        rueda3 = new GEBalljoint(
            1.0f,
            glm::vec3(-2.0f, 0.0f, 2.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

        rueda3->initialize(gc, rc, principal->getMatriz());
        rueda3->setLight(light);
        principal->addHijo(rueda3);

        rueda4 = new GEBalljoint(
            1.0f,
            glm::vec3(-2.0f, 0.0f, -5.4f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        rueda4->initialize(gc, rc, principal->getMatriz());
        rueda4->setLight(light);
        principal->addHijo(rueda4);

    computeMatrix();
}

//
// FUNCIÓN: GESkeletonCoche::setPose(std::vector<glm::vec3> pose)
//
// PROPÓSITO: Asigna los angulos de euler a cada articulación
//
void GESkeletonCoche::setPose(std::vector<glm::vec3> pose) {

    principal->setPose(pose[0]);
    rueda1->setPose(pose[1]);
    rueda2->setPose(pose[2]);
    rueda3->setPose(pose[3]);
    rueda4->setPose(pose[4]);
}