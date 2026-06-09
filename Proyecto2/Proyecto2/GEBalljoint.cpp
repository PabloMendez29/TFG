#include "GEBalljoint.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//
// FUNCIÓN: GEBalljoint::GEBalljoint(float l, glm::vec3 offset, glm::vec3 right, glm::vec3 up)
//
// PROPÓSITO: Construye una articulación.
//
GEBalljoint::GEBalljoint(float l, glm::vec3 offset, glm::vec3 right, glm::vec3 up)
{
    length = l;

    location = offset;

    this->right = right; //xaxis
    this->up = up; //yaxis
    dir = glm::cross(right, up); //zaxis

    angles[0] = 0.0f;
    angles[1] = 0.0f;
    angles[2] = 0.0f;

    joint = nullptr;
    bone = nullptr;

}



//
// FUNCIÓN: GEBalljoint::ComputeMatrix(glm::mat4 parent)
//
// PROPÓSITO: Crea la matriz de transformación a partir de la posición, 
//            la orientación y la pose.
//
void GEBalljoint::ComputeMatrix(glm::mat4 parent)
{
    // Formato glm::mat4[column][row]
    glm::mat4 jointm;
    jointm[0][0] = right.x;
    jointm[0][1] = right.y;
    jointm[0][2] = right.z;
    jointm[0][3] = 0.0;

    jointm[1][0] = up.x;
    jointm[1][1] = up.y;
    jointm[1][2] = up.z;
    jointm[1][3] = 0.0;

    jointm[2][0] = dir.x;
    jointm[2][1] = dir.y;
    jointm[2][2] = dir.z;
    jointm[2][3] = 0.0;

    jointm[3][0] = location.x;
    jointm[3][1] = location.y;
    jointm[3][2] = location.z;
    jointm[3][3] = 1.0;

    float cx = (float)cos(glm::radians(angles[0]));
    float sx = (float)sin(glm::radians(angles[0]));
    float cy = (float)cos(glm::radians(angles[1]));
    float sy = (float)sin(glm::radians(angles[1]));
    float cz = (float)cos(glm::radians(angles[2]));
    float sz = (float)sin(glm::radians(angles[2]));

    glm::mat4 posem;
    posem[0][0] = cz * cy;
    posem[1][0] = -sz * cx + cz * sy * sx;
    posem[2][0] = sz * sx + cz * sy * cx;
    posem[3][0] = 0;

    posem[0][1] = sz * cy;
    posem[1][1] = cz * cx + sz * sy * sx;
    posem[2][1] = -cz * sx + sz * sy * cx;
    posem[3][1] = 0;

    posem[0][2] = -sy;
    posem[1][2] = cy * sx;
    posem[2][2] = cy * cx;
    posem[3][2] = 0;

    posem[0][3] = 0;
    posem[1][3] = 0;
    posem[2][3] = 0;
    posem[3][3] = 1;

    this->matrizPadre = parent;

    matrix = matrizPadre * jointm * posem;


    joint->setLocation(matrix);
    glm::mat4 mm = glm::translate(matrix, glm::vec3(0.0f, 0.0f, length / 2));
    bone->setLocation(mm);

    glm::mat4 mchild = glm::translate(matrix, glm::vec3(0.0f, 0.0f, length));

    for (GEBalljoint* hijo : hijos)
        hijo->ComputeMatrix(mchild);
}

//
// FUNCIÓN: GEBalljoint::initialize(GEGraphicsContext* gc, GERenderingContext* rc, glm::mat4 parent)
//
// PROPÓSITO: Inicializa las piezas de la articulación
//
void GEBalljoint::initialize(GEGraphicsContext* gc, GERenderingContext* rc, glm::mat4 parent)
{
    GEMaterial jointMat = {};
    jointMat.Ka = glm::vec3(1.0f, 0.0f, 0.0f);
    jointMat.Kd = glm::vec3(1.0f, 0.0f, 0.0f);
    jointMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    jointMat.Shininess = 16.0f;

    joint = new GESphere(10, 20, 0.1f);
    joint->initialize(gc, rc);
    joint->setMaterial(jointMat);

    GEMaterial boneMat = {};
    boneMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
    boneMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
    boneMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    boneMat.Shininess = 16.0f;

    bone = new GECylinder(2, 10, 0.05f, length / 2);
    bone->initialize(gc, rc);
    bone->setMaterial(boneMat);

    this->matrizPadre = matrizPadre;

    ComputeMatrix(this->matrizPadre);
}



//
// FUNCIÓN: GEBalljoint::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes
//
void GEBalljoint::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
{
    joint->update(gc, index, view, projection);
    bone->update(gc, index, view, projection);

    for (GEBalljoint* hijo : hijos)
        hijo->update(gc, index, view, projection);
}

//
// FUNCIÓN: GEBalljoint::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Destruye los buffers de las piezas
//
void GEBalljoint::destroy(GEGraphicsContext* gc)
{
    joint->destroy(gc);
    bone->destroy(gc);

    delete joint;
    delete bone;

    for (GEBalljoint* hijo : hijos)
        hijo->destroy(gc);
}

//
// FUNCIÓN: GEBalljoint::setLocation(glm::vec3 loc)
//
// PROPÓSITO: Asigna la posición de la articulación
//
void GEBalljoint::setLocation(glm::vec3 loc)
{
    location = loc;
    ComputeMatrix(matrizPadre);
}

//
// FUNCIÓN: GEBalljoint::setOrientation(glm::vec3 right, glm::vec3 up)
//
// PROPÓSITO: Asigna la orientación de la articulación (con pose 0,0,0).
//
void GEBalljoint::setOrientation(glm::vec3 right, glm::vec3 up)
{
    this->right = right;
    this->up = up;
    dir = glm::cross(right, up);
    ComputeMatrix(matrizPadre);
}

//
// FUNCIÓN: GEBalljoint::setPose(glm::vec3 pose)
//
// PROPÓSITO: Asigna la rotación de la articulación
//

void GEBalljoint::setPose(glm::vec3 pose)
{

    angles[0] = pose.x;
    angles[1] = pose.y;
    angles[2] = pose.z;

    ComputeMatrix(matrizPadre);
}

//
// FUNCIÓN: GEBalljoint::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
//
// PROPÓSITO: Añade los comandos de dibujo
//
void GEBalljoint::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
    joint->addCommands(commandBuffer, pipelineLayout, index);
    bone->addCommands(commandBuffer, pipelineLayout, index);

    for (GEBalljoint* hijo : hijos)
        hijo->addCommands(commandBuffer, pipelineLayout, index);
}

//
// FUNCIÓN: GEBalljoint::setLight(GELight l)
//
// PROPÓSITO: Asigna las propiedades de la luz
//
void GEBalljoint::setLight(GELight l)
{
    joint->setLight(l);
    bone->setLight(l);

    for (GEBalljoint* hijo : hijos)
        hijo->setLight(l);
}

//
// FUNCIÓN: GEBalljoint::getHijos()
//
// PROPÓSITO: Devuelve las articulaciones hijas de la clase
//
std::vector<GEBalljoint*> GEBalljoint::getHijos() {
    return hijos;
}

//
// FUNCIÓN: GEBalljoint::addHijo(GEBalljoint* hijo)
//
// PROPÓSITO: Añade una articulacion hija a la clase
//
void GEBalljoint::addHijo(GEBalljoint* hijo) {
    hijo->padre = this;
    hijos.push_back(hijo);
    hijo->location = glm::vec3(hijo->location.x, hijo->location.y, hijo->location.z);
    ComputeMatrix(matrizPadre);
}

//
// FUNCIÓN: GEBalljoint::getMatriz()
//
// PROPÓSITO: Devuelve la matriz de transformacion
//
glm::mat4 GEBalljoint::getMatriz() {
    return matrix;
}

//
// FUNCIÓN: GEBalljoint::computeBindingMatrix(glm::mat4 parent)
//
// PROPÓSITO: Crea la matriz aglutinante (inversa de la matriz de mundo en modo reposo)
//
void GEBalljoint::computeBindingMatrix(glm::mat4 parent)
{
    // Formato glm::mat4[column][row]
    glm::mat4 jointm;
    jointm[0][0] = right.x;
    jointm[0][1] = right.y;
    jointm[0][2] = right.z;
    jointm[0][3] = 0.0;

    jointm[1][0] = up.x;
    jointm[1][1] = up.y;
    jointm[1][2] = up.z;
    jointm[1][3] = 0.0;

    jointm[2][0] = dir.x;
    jointm[2][1] = dir.y;
    jointm[2][2] = dir.z;
    jointm[2][3] = 0.0;

    jointm[3][0] = location.x;
    jointm[3][1] = location.y;
    jointm[3][2] = location.z;
    jointm[3][3] = 1.0;

    glm::mat4 mm = parent * jointm;
    this->bindingMatrix = glm::inverse(mm);

    glm::mat4 childM = glm::translate(mm, glm::vec3(0.0f, 0.0f, length));

    for (GEBalljoint* hijo : hijos)
        hijo->computeBindingMatrix(childM);
}


//
// FUNCIÓN: GEBalljoint::getJointMatrix())
//
// PROPÓSITO: Obtiene la matriz Joint
//
glm::mat4 GEBalljoint::getJointMatrix()
{
    return matrix * bindingMatrix;
}

//
// FUNCIÓN: GEBalljoint::getJointMatrix())
//
// PROPÓSITO: Devuelve la matriz Joint
//
void GEBalljoint::getJointMatrixs(std::vector<glm::mat4>& list) {

    list.push_back(getJointMatrix());

    for (GEBalljoint* hijo : hijos)
        hijo->getJointMatrixs(list);
}