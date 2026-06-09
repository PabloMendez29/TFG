#include "GEScene.h"

#include "GESphere.h"
#include "GEGround.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include <windows.h>
#include "resource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GETexture.h"
#include "GEVertexRigid.h"
#include "GECubeMorphing.h"

#define RIGID_PIPELINE 0
#define MORPHING_PIPELINE 1
#define MORPHING_LINE_PIPELINE 2

//
// FUNCIÓN: GEScene::GEScene(GEGraphicsContext* gc, GEDrawingContext* dc)
//
// PROPÓSITO: Crea la escena
//
GEScene::GEScene(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc)
{
	VkExtent2D extent = dc->getExtent();
	double aspect = (double)extent.width / (double)extent.height;
	aspect_ratio(aspect);

	GEPipelineConfig* configRigid = createPipelineConfigRigid(dc->getExtent());
	GEPipelineConfig* configMorphing = createPipelineConfigMorphing(dc->getExtent());
	GEPipelineConfig* configMorphingLine = createPipelineConfigMorphingLine(dc->getExtent());

	rc = new GERenderingContext(gc, dc, configRigid);
	rc->addGraphicsPipeline(gc, configMorphing);
	rc->addGraphicsPipeline(gc, configMorphingLine);

	rc->setActivePipeline(RIGID_PIPELINE);
	
	
	tick = 0;

	this->camera = new GECamera();
	this->camera->setPosition(glm::vec3(0.0f, 1.0f, 15.0f));
	this->camera->setDirection(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->camera->setMoveStep(0.0f);


	GELight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.2f, 0.2f, 0.2f);
	light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	GEMaterial groundMat = {};
	groundMat.Ka = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Kd = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	groundMat.Shininess = 16.0f;

	
	ground = new GEGround(10.0f, 10.0f);
	ground->initialize(gc, rc);
	ground->setLight(light);
	ground->setMaterial(groundMat);
	ground->translate(glm::vec3(0.0f, -2.0f, 0.0f));
	

	GEMaterial whiteMat = {};
	whiteMat.Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Shininess = 16.0f;

	GEMaterial redMat = {};
	redMat.Ka = glm::vec3(0.7f, 0.0f, 0.0f);
	redMat.Kd = glm::vec3(0.7f, 0.0f, 0.0f);
	redMat.Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	redMat.Shininess = 16.0f;


	GETexture* ladrillos = new GETexture(gc, "textures/bricks.jpg");
	GETexture* madera = new GETexture(gc, "textures/wood.jpg");
	GETexture* blanco = new GETexture(gc, "textures/Blanco.jpg");


	rc->setActivePipeline(MORPHING_PIPELINE);

	
	cuboFill = new GECubeMorphing(2.0f, 10);
	cuboFill->setTextures(ladrillos, madera);
	cuboFill->initialize(gc, rc);
	cuboFill->setLight(light);
	cuboFill->setMaterial(whiteMat);
	cuboFill->translate(glm::vec3(-3.0f, 0.0f, 0.0f));


	rc->setActivePipeline(MORPHING_LINE_PIPELINE);

	cuboLine = new GECubeMorphing(2.0f, 10);
	cuboLine->setTextures(blanco, blanco);
	cuboLine->initialize(gc, rc);
	cuboLine->setLight(light);
	cuboLine->setMaterial(redMat);
	cuboLine->translate(glm::vec3(3.0f, 0.0f, 0.0f));



	
	fillCommandBuffers(cc);
}

//
// FUNCIÓN: GEScene::destroy(GEGraphicsContext* gc)
//
// PROPÓSITO: Reconstruye los componentes gráficos de la escena
//
void GEScene::destroy(GEGraphicsContext* gc)
{
	ground->destroy(gc);

	cuboFill->destroy(gc);
	cuboLine->destroy(gc);

	rc->destroy(gc);
		

	delete ground;

	delete cuboFill;
	delete cuboLine;

	delete rc;
}

//
// FUNCIÓN: GEScene::recreate(GEGraphicsContext* gc, GEDrawingContext* dc)
//
// PROPÓSITO: Reconstruye los componentes gráficos de la escena
//
void GEScene::recreate(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc)
{
	
	rc->destroy(gc);

	GEPipelineConfig* configRigid = createPipelineConfigRigid(dc->getExtent());
	GEPipelineConfig* configMorphing = createPipelineConfigMorphing(dc->getExtent());
	GEPipelineConfig* configMorphingLine = createPipelineConfigMorphingLine(dc->getExtent());

	rc = new GERenderingContext(gc, dc, configRigid);
	rc->addGraphicsPipeline(gc, configMorphing);
	rc->addGraphicsPipeline(gc, configMorphingLine);

	fillCommandBuffers(cc);
}

//
// FUNCIÓN: GEScene::update(GEGraphicsContext* gc, uint32_t index)
//
// PROPÓSITO: Actualiza la información para generar la imagen 
//
void GEScene::update(GEGraphicsContext* gc, uint32_t index)
{
	camera->update();
	glm::mat4 view = camera->getViewMatrix();



	tick = tick + v;
	if (tick > 25) {
		v = -v;
	}
	if (tick < -5) {
		v = -v;
	}


	ground->update(gc, index, view, projection);


	cuboFill->update(gc, index, view, projection, glm::clamp(tick, 0.0f, 20.0f) / 20);
	cuboLine->update(gc, index, view, projection, glm::clamp(tick, 0.0f, 20.0f) / 20);

}

//
// FUNCIÓN: GEScene::key_action(int key, bool pressed)
//
// PROPÓSITO: Respuesta a acciones de teclado
//
void GEScene::key_action(int key, bool pressed)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		camera->setTurnDown(pressed);
		break;
	case GLFW_KEY_DOWN:
		camera->setTurnUp(pressed);
		break;
	case GLFW_KEY_LEFT:
		camera->setTurnCCW(pressed);
		break;
	case GLFW_KEY_RIGHT:
		camera->setTurnCW(pressed);
		break;
	case GLFW_KEY_S:
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_KP_ADD:
	case GLFW_KEY_1:
		camera->setMoveStep(camera->getMoveStep() + 0.1f);
		break;
	case GLFW_KEY_KP_SUBTRACT:
	case GLFW_KEY_2:
		camera->setMoveStep(camera->getMoveStep() - 0.1f);
		break;
	case GLFW_KEY_Q:
		camera->setMoveUp(pressed);
		break;
	case GLFW_KEY_A:
		camera->setMoveDown(pressed);
		break;
	case GLFW_KEY_O:
		camera->setMoveLeft(pressed);
		break;
	case GLFW_KEY_P:
		camera->setMoveRight(pressed);
		break;
	case GLFW_KEY_K:
		camera->setTurnLeft(pressed);
		break;
	case GLFW_KEY_L:
		camera->setTurnRight(pressed);
		break;
	}
}

//
// FUNCIÓN: GEScene::aspect_ratio(double)
//
// PROPÓSITO: Modifica la relación anchura/altura del modelo
//
void GEScene::aspect_ratio(double aspect)
{
	constexpr double fov = glm::radians(30.0f);
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	float wHeight = (float)(sin_fov * 0.2 / cos_fov);
	float wWidth = (float)(wHeight * aspect);

	projection = glm::perspective((float)fov, (float)aspect, 0.2f, 400.0f);
	projection[1][1] *= -1.0f;
}

//
// FUNCIÓN: GEScene::createPipelineConfigRigid()
//
// PROPÓSITO: Obtiene la configuración del pipeline de renderizado normal
//
GEPipelineConfig* GEScene::createPipelineConfigRigid(VkExtent2D extent)
{
	GEPipelineConfig* config = new GEPipelineConfig();
	config->vertex_shader = IDR_HTML1;
	config->fragment_shader = IDR_HTML2;

	config->attrStride = sizeof(GEVertexRigid);
	config->attrOffsets.resize(2);
	config->attrOffsets[0] = offsetof(GEVertexRigid, pos);
	config->attrOffsets[1] = offsetof(GEVertexRigid, norm);
	config->attrFormats.resize(2);
	config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;

	config->descriptorTypes.resize(3);
	config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorStages.resize(3);
	config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;

	config->depthTestEnable = VK_TRUE;
	config->cullMode = VK_CULL_MODE_BACK_BIT;
	config->extent = extent;

	return config;
}


//
// FUNCIÓN: GEScene::createPipelineConfigMorphing()
//
// PROPÓSITO: Obtiene la configuración del pipeline de renderizado para Morphing
//
GEPipelineConfig* GEScene::createPipelineConfigMorphing(VkExtent2D extent)
{
	GEPipelineConfig* config = new GEPipelineConfig();
	config->vertex_shader = IDR_HTML3;
	config->fragment_shader = IDR_HTML4;

	config->attrStride = sizeof(GEVertexMorphing);
	config->attrOffsets.resize(5);
	config->attrOffsets[0] = offsetof(GEVertexMorphing, pos1);
	config->attrOffsets[1] = offsetof(GEVertexMorphing, norm1);
	config->attrOffsets[2] = offsetof(GEVertexMorphing, pos2);
	config->attrOffsets[3] = offsetof(GEVertexMorphing, norm2);
	config->attrOffsets[4] = offsetof(GEVertexMorphing, tex);
	config->attrFormats.resize(5);
	config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[2] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[3] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[4] = VK_FORMAT_R32G32_SFLOAT;


	config->descriptorTypes.resize(6);
	config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;	
	config->descriptorTypes[3] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[4] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorTypes[5] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorStages.resize(6);
	config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[3] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[4] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[5] = VK_SHADER_STAGE_FRAGMENT_BIT;

	config->depthTestEnable = VK_TRUE;
	config->cullMode = VK_CULL_MODE_BACK_BIT;
	config->extent = extent;

	return config;
}

//
// FUNCIÓN: GEScene::createPipelineConfigMorphing()
//
// PROPÓSITO: Obtiene la configuración del pipeline de renderizado para Morphing con modo aristas
//
GEPipelineConfig* GEScene::createPipelineConfigMorphingLine(VkExtent2D extent)
{
	GEPipelineConfig* config = new GEPipelineConfig();
	config->vertex_shader = IDR_HTML3;
	config->fragment_shader = IDR_HTML4;

	config->attrStride = sizeof(GEVertexMorphing);
	config->attrOffsets.resize(5);
	config->attrOffsets[0] = offsetof(GEVertexMorphing, pos1);
	config->attrOffsets[1] = offsetof(GEVertexMorphing, norm1);
	config->attrOffsets[2] = offsetof(GEVertexMorphing, pos2);
	config->attrOffsets[3] = offsetof(GEVertexMorphing, norm2);
	config->attrOffsets[4] = offsetof(GEVertexMorphing, tex);
	config->attrFormats.resize(5);
	config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[2] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[3] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[4] = VK_FORMAT_R32G32_SFLOAT;


	config->descriptorTypes.resize(6);
	config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[3] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[4] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorTypes[5] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorStages.resize(6);
	config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[3] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[4] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[5] = VK_SHADER_STAGE_FRAGMENT_BIT;

	config->depthTestEnable = VK_TRUE;
	config->cullMode = VK_CULL_MODE_NONE;
	config->extent = extent;

	config->polygonMode = VK_POLYGON_MODE_LINE;

	return config;
}

//
// FUNCIÓN: GEScene::fillCommandBuffers(std::vector<VkCommandBuffer> commandBuffers)
//
// PROPÓSITO: Rellena los buffers de comandos
//
void GEScene::fillCommandBuffers(GECommandContext* cc)
{
	cc->beginCommandBuffers();
	rc->insertBeginCommands(cc->commandBuffers);
	
	rc->setActivePipeline(RIGID_PIPELINE);
	rc->insertPipelineCommands(cc->commandBuffers);
	for (int i = 0; i < cc->commandBuffers.size(); i++)
	{
		ground->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}
	
	rc->setActivePipeline(MORPHING_PIPELINE);
	rc->insertPipelineCommands(cc->commandBuffers);
	for (int i = 0; i < cc->commandBuffers.size(); i++)
	{
		cuboFill->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}

	rc->setActivePipeline(MORPHING_LINE_PIPELINE);
	rc->insertPipelineCommands(cc->commandBuffers);
	for (int i = 0; i < cc->commandBuffers.size(); i++)
	{
		cuboLine->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}
	
	rc->insertEndCommands(cc->commandBuffers);
	cc->endCommandBuffers();
}