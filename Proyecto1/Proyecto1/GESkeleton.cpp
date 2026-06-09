#include "GESkeleton.h"
#include <glm/ext/matrix_transform.hpp>


//
// FUNCIÓN: GESkeleton::GESkeleton(glm::vec3 offset, glm::vec3 right, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light)
//
// PROPÓSITO: Contruye el esqueleto
//
GESkeleton::GESkeleton(glm::vec3 offset, glm::vec3 right, glm::vec3 up, GEGraphicsContext* gc, GERenderingContext* rc, GELight light) {

    this->gc = gc;
    this->rc = rc;

	location = offset;

    this->right = right; //xaxis
    this->up = up; //yaxis
    
    dir = glm::cross(right, up); //zaxis

    computeMatrix();

}   

//
// FUNCIÓN: GESkeleton::~GESkeleton()
//
// PROPÓSITO: Destruye el esqueleto junto a sus articulaciones
//
GESkeleton::~GESkeleton() {

    for (GEBalljoint* hijo : hijos) {
        delete hijo;
    }
}

//
// FUNCIÓN: GESkeleton::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Llama a destroy a todas sus articulaciones
//
void GESkeleton::destroy(GEGraphicsContext* gc)
{

    for (GEBalljoint* hijo : hijos)
        hijo->destroy(gc);
}

//
// FUNCIÓN: GESkeleton::computeMatrix()
//
// PROPÓSITO: Calcula ma matriz de transformación
//
void GESkeleton::computeMatrix() {

    //std::cout << "HijosRM: " << hijos.size() << std::endl;

    matrizCuerpo[0][0] = right.x;
    matrizCuerpo[0][1] = right.y;
    matrizCuerpo[0][2] = right.z;
    matrizCuerpo[0][3] = 0.0;

    matrizCuerpo[1][0] = up.x;
    matrizCuerpo[1][1] = up.y;
    matrizCuerpo[1][2] = up.z;
    matrizCuerpo[1][3] = 0.0;

    matrizCuerpo[2][0] = dir.x;
    matrizCuerpo[2][1] = dir.y;
    matrizCuerpo[2][2] = dir.z;
    matrizCuerpo[2][3] = 0.0;

    matrizCuerpo[3][0] = location.x;
    matrizCuerpo[3][1] = location.y;
    matrizCuerpo[3][2] = location.z;
    matrizCuerpo[3][3] = 1.0;

    for (auto* hijo : hijos) {
        hijo->ComputeMatrix(matrizCuerpo);
    }
}

//
// FUNCIÓN: GESkeleton::setLocation(glm::vec3 loc)
//
// PROPÓSITO: Asigna la posición del esqueleto
//
void GESkeleton::setLocation(glm::vec3 loc) {
    location = loc;
    computeMatrix();
}

//
// FUNCIÓN: GESkeleton::setOrientation(glm::vec3 nRight, glm::vec3 nUp) {
//
// PROPÓSITO: Asigna la orientacion del esqueleto
//
void GESkeleton::setOrientation(glm::vec3 nRight, glm::vec3 nUp) {
    this->right = nRight;
    this->up = nUp;
    dir = glm::cross(right, up);

    computeMatrix();
}

//
// FUNCIÓN: GESkeleton::translate(glm::vec3 loc)
//
// PROPÓSITO: Despalza la posicion del esqueleto
//
void GESkeleton::translate(glm::vec3 loc)
{
    location = glm::vec3(location.x + loc.x, location.y + loc.y, location.z + loc.z);
    computeMatrix();
}

//
// FUNCIÓN: GESkeleton::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Llama a update a todas sus articulaicones
//
void GESkeleton::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection) {
    for (auto* hijo : hijos) {
        hijo->update(gc, index, view, projection);
    }
}

//
// FUNCIÓN: GESkeleton::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index) 
//
// PROPÓSITO: Añade los comandos de dibujo
//
void GESkeleton::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index){
    for (auto* hijo : hijos) {
        hijo->addCommands(commandBuffer, pipelineLayout, index);
    }
}

//
// FUNCIÓN: GESkeleton::computeBindingMatrixs() 
//
// PROPÓSITO: Llama a computeBindingMatrixs a todas sus articulaicones
//
void GESkeleton::computeBindingMatrixs()
{
    for (auto* hijo : hijos)
        hijo->computeBindingMatrix(matrizCuerpo);


}

//
// FUNCIÓN: GESkeleton::getJointMatrixs() 
//
// PROPÓSITO: Devuelve un vector de todas las JointMatrixs
//
std::vector<glm::mat4> GESkeleton::getJointMatrixs() {

    std::vector<glm::mat4> JointMatrixList;

    for (auto* hijo : hijos) {
        hijo->getJointMatrixs(JointMatrixList);
    }

    return JointMatrixList;
}