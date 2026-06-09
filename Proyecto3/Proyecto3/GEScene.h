#pragma once

#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GECommandContext.h"
#include "GERenderingContext.h"

#include "GEFigureRigid.h"
#include "GEFigureMorphing.h"
#include "GECamera.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>


//
// CLASE: GEScene
//
// DESCRIPCIÓN: Clase que describe una escena
//
class GEScene
{
private:
	GERenderingContext* rc;
	GEFigureRigid* ground;

	GEFigureMorphing* cuboFill;
	GEFigureMorphing* cuboLine;

	GECamera* camera;
	glm::mat4 projection;

	float v = 0.1f;

	float tick;

public:
	GEScene(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);
	void destroy(GEGraphicsContext* gc);
	void recreate(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);
	void update(GEGraphicsContext* gc, uint32_t index);
	void key_action(int key, bool pressed);
	void aspect_ratio(double aspect);

private:
	GEPipelineConfig* createPipelineConfigRigid(VkExtent2D extent);
	GEPipelineConfig* createPipelineConfigMorphing(VkExtent2D extent);
	GEPipelineConfig* createPipelineConfigMorphingLine(VkExtent2D extent);
	void fillCommandBuffers(GECommandContext* cc);
};

