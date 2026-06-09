	#pragma once

	#include "GEGraphicsContext.h"
	#include "GERenderingContext.h"
	#include "GEFigureAnimated.h"
	#include "GEPiece.h"
	
	//
	// CLASE: GEObject
	//
	// DESCRIPCIÓN: Clases que representa una figura formada por varias piezas
	//
	class GEObject
	{
	public:
		void initalize(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<glm::mat4> jointMatrixs);
		void finalize(GEGraphicsContext* gc);
		void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
		void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection, std::vector<glm::mat4> jointMatrixs);
		
		glm::mat4 GetLocation();

		void Translate(glm::vec3 t);
		void Rotate(GLfloat angle, glm::vec3 axis);
		void Scale(glm::vec3 scale);

		void ResetLocation();
		void SetLocation(glm::mat4 loc);
		void setLight(GELight l);
		void setMaterial(GEMaterial m);
		void setTexture(GETexture* texture);

		virtual int GetNumPieces() = 0;
		virtual GEPiece* GetPiece(int i) = 0;


		public:
			glm::mat4 location;
	};

