#include "GEObject.h"
#include <glm/gtc/matrix_transform.hpp>

// FUNCIÓN: GEObject::initalize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> matrices)
//
// PROPÓSITO: Inicializa cada pieza
//
void GEObject::initalize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs) {
	
	location = glm::mat4(1);

	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->initialize(gc, rc, jointMatrixs);
	}
}

//
// FUNCIÓN: GEObject::finalize(GEGraphicsContext* gc)
//
// PROPÓSITO: Libera los buffers de las piezas que forman el objeto
//
void GEObject::finalize(GEGraphicsContext* gc)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->finalize(gc);
	}
}


// FUNCION: GEObject::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer para cada pieza del objeto
//
void GEObject::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->addCommands(commandBuffer, pipelineLayout, index);
	}
}

//
// FUNCIÓN: GEObject::update(GEGraphicsContext* gc, uint32_t index,  glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> matrices)
//
// PROPÓSITO:  Actualiza las variables uniformes sobre una imagen del swapchain de cada pieza del objeto
//
void GEObject::update(GEGraphicsContext* gc, uint32_t index,  glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->update(gc, index, location, view, projection, jointMatrixs);
	}
}


//
// FUNCIÓN: GEObject::ResetLocation()
//
// PROPÓSITO: Asigna la posición inicial del objecto 
//
void GEObject::ResetLocation()
{
	location = glm::mat4(1.0f);

}

//
// FUNCIÓN: GEObject::SetLocation(glm::mat4 loc)
//
// PROPÓSITO: Asigna la posición del objecto 
//
void GEObject::SetLocation(glm::mat4 loc)
{
	location = loc;
}

//
// FUNCIÓN: GEObject::Translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento a la matriz de posición del objeto 
//
void GEObject::Translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}


//
// FUNCIÓN: GEObject::Rotate(GLfloat angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación a la matriz de posición del objeto 
//
void GEObject::Rotate(GLfloat angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: GEObject::Scale(glm::vec3 scale)
//
// PROPÓSITO: Modifica la escala del objeto 
//
void GEObject::Scale(glm::vec3 scale)
{
	location = glm::scale(location, scale);
}

//
// FUNCIÓN: GEObject::GetLocation()
//
// PROPÓSITO: Obtiene la posición del objecto 
//
glm::mat4 GEObject::GetLocation()
{
	return location;
}



//
// FUNCIÓN: GEObject::setLight(CALight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que incide en la figura
//
void GEObject::setLight(GELight l)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->setLight(l);
	}
}

//
// FUNCIÓN: GEObject::setMaterial(GEMaterial m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la figura
//
void GEObject::setMaterial(GEMaterial m)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->setMaterial(m);
	}
}

//
// FUNCIÓN: GEObject::setTexture(GETexture* t)
//
// PROPÓSITO: Asigna las propiedades la textura a la figura
//
void GEObject::setTexture(GETexture* t)
{
	for (int i = 0; i < GetNumPieces(); i++)
	{
		GetPiece(i)->setTexture(t);
	}
}


