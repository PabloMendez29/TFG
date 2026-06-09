#pragma once

#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GECommandContext.h"
#include "GERenderingContext.h"

#include "GETorus.h"
#include "GEFigureRigid.h"
#include "GEFigureAnimated.h"
#include "GEBalljoint.h"
#include "GECamera.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include "GESkeleton.h"
#include "GEListaPoses.h"
#include "GEAnimation.h"

#include "GECoche.h"
//
// CLASE: GEScene
//
// DESCRIPCIÓN: Clase que describe una escena
//
class GEScene
{
private:
	GERenderingContext* rc;
	GECommandContext* cc;
	GEFigureRigid* ground;
	GEFigureRigid* balon;

	GEFigureRigid* aro;
	GEFigureRigid* palo;
	GEFigureRigid* cuadro;

	GEFigureAnimated* cilindro;
	GEFigureAnimated* cubo;

	GECamera* camera;
	glm::mat4 projection;

	GEListaPoses* prueba;

	GEAnimation* animacionFill;
	GEAnimation* animacionLine;

	GESkeleton* esqueletoFill;
	GESkeleton* esqueletoLine;

	GECoche* cocheFill;
	GECoche* cocheLine;

	float tick;

	bool verEsqueleto;

public:
	GEScene(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);
	void destroy(GEGraphicsContext* gc);
	void recreate(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);
	void update(GEGraphicsContext* gc, uint32_t index);
	void key_action(int key, bool pressed);
	void aspect_ratio(double aspect);

private:
	GEPipelineConfig* createPipelineConfigRigid(VkExtent2D extent);
	GEPipelineConfig* createPipelineConfigAnimated(VkExtent2D extent);
	GEPipelineConfig* createPipelineConfigAnimatedLine(VkExtent2D extent);
	void fillCommandBuffers(GECommandContext* cc);
};

