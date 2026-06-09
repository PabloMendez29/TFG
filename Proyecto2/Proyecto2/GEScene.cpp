#include "GEScene.h"

#include "GECylinder.h"
#include "GECylinderAnimated.h"
#include "GECubeAnimated.h"
#include "GESphere.h"
#include "GEGround.h"
#include "GEBalljoint.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include "GESkeletonCylinder.h"
#include <windows.h>
#include "resource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GETexture.h"
#include "GEVertexAnimated.h"
#include "GEVertexRigid.h"

#define RIGID_PIPELINE 0
#define ANIMATED_PIPELINE 1
#define ANIMATED_LINE_PIPELINE 2

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
	GEPipelineConfig* configAnimated = createPipelineConfigAnimated(dc->getExtent());
	GEPipelineConfig* configAnimatedLine = createPipelineConfigAnimatedLine(dc->getExtent());

	rc = new GERenderingContext(gc, dc, configRigid);
	rc->addGraphicsPipeline(gc, configAnimated);
	rc->addGraphicsPipeline(gc, configAnimatedLine);

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
	
	GEMaterial blueMat = {};
	blueMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	blueMat.Shininess = 16.0f;

	GEMaterial orangeMat = {};
	orangeMat.Ka = glm::vec3(1.0f, 0.2f, 0.0f);
	orangeMat.Kd = glm::vec3(1.0f, 0.2f, 0.0f);
	orangeMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	orangeMat.Shininess = 16.0f;

	GEMaterial whiteMat = {};
	whiteMat.Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	whiteMat.Shininess = 16.0f;

	GEMaterial brownMat = {};
	brownMat.Ka = glm::vec3(0.7f, 0.1f, 0.05f);    
	brownMat.Kd = glm::vec3(0.6f, 0.2f, 0.1f);     
	brownMat.Ks = glm::vec3(0.1f, 0.1f, 0.1f);     
	brownMat.Shininess = 8.0f;

	GETexture* ladrillos = new GETexture(gc, "textures/bricks.jpg");
	GETexture* blanco = new GETexture(gc, "textures/Blanco.jpg");

	esqueletoFill = new GESkeletonCylinder(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), gc, rc, light);
	esqueletoFill->computeBindingMatrixs();
	esqueletoFill->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	esqueletoFill->translate(glm::vec3(-3.0f, 0.0f, 0.0f));

	esqueletoLine = new GESkeletonCylinder(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), gc, rc, light);
	esqueletoLine->computeBindingMatrixs();
	esqueletoLine->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	esqueletoLine->translate(glm::vec3(3.0f, 0.0f, 0.0f));


	rc->setActivePipeline(ANIMATED_PIPELINE);


	cilindroFill = new GECylinderAnimated(10, 16, 0.5f, 2.0f);
	cilindroFill->setTexture(ladrillos);
	cilindroFill->initialize(gc, rc, esqueletoFill->getJointMatrixs());
	cilindroFill->setLight(light);
	cilindroFill->setMaterial(whiteMat);

	rc->setActivePipeline(ANIMATED_LINE_PIPELINE);


	cilindroLine = new GECylinderAnimated(10, 16, 0.5f, 2.0f);
	cilindroLine->setTexture(blanco);
	cilindroLine->initialize(gc, rc, esqueletoLine->getJointMatrixs());
	cilindroLine->setLight(light);
	cilindroLine->setMaterial(orangeMat);

	prueba = new GEListaPoses();
	animacionFill = new GEAnimation(esqueletoFill, prueba->getKeyframes());
	animacionLine = new GEAnimation(esqueletoLine, prueba->getKeyframes());
	
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

	cilindroFill->destroy(gc);
	cilindroLine->destroy(gc);

	esqueletoFill->destroy(gc);

	rc->destroy(gc);
		
	delete ground;

	delete cilindroFill;
	delete cilindroLine;

	delete esqueletoFill;
	delete esqueletoLine;

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
	GEPipelineConfig* configAnimated = createPipelineConfigAnimated(dc->getExtent());
	GEPipelineConfig* configAnimatedLine = createPipelineConfigAnimatedLine(dc->getExtent());

	rc = new GERenderingContext(gc, dc, configRigid);
	rc->addGraphicsPipeline(gc, configAnimated);
	rc->addGraphicsPipeline(gc, configAnimatedLine);

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

	tick = tick + 0.1;
	if (tick > 20) {
		tick = 0;
	}

	animacionFill->actualizaEsqueleto(tick);
	animacionLine->actualizaEsqueleto(tick);

	ground->update(gc, index, view, projection);

	esqueletoFill->update(gc, index, view, projection);
	esqueletoLine->update(gc, index, view, projection);

	cilindroFill->update(gc, index, view, projection, esqueletoFill->getJointMatrixs());
	cilindroLine->update(gc, index, view, projection, esqueletoLine->getJointMatrixs());

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
// PROPÓSITO: Obtiene la configuración del pipeline de renderizado
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
// FUNCIÓN: GEScene::createPipelineConfigAnimated()
//
// PROPÓSITO: Obtiene la configuración del pipeline de renderizado
//
GEPipelineConfig* GEScene::createPipelineConfigAnimated(VkExtent2D extent)
{
	GEPipelineConfig* config = new GEPipelineConfig();
	config->vertex_shader = IDR_HTML3;
	config->fragment_shader = IDR_HTML4;

	config->attrStride = sizeof(GEVertexAnimated);
	config->attrOffsets.resize(5);
	config->attrOffsets[0] = offsetof(GEVertexAnimated, pos);
	config->attrOffsets[1] = offsetof(GEVertexAnimated, norm);
	config->attrOffsets[2] = offsetof(GEVertexAnimated, tex);
	config->attrOffsets[3] = offsetof(GEVertexAnimated, weights);
	config->attrOffsets[4] = offsetof(GEVertexAnimated, indices);
	config->attrFormats.resize(5);
	config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[2] = VK_FORMAT_R32G32_SFLOAT;
	config->attrFormats[3] = VK_FORMAT_R32G32B32A32_SFLOAT;
	config->attrFormats[4] = VK_FORMAT_R32G32B32A32_SINT;


	config->descriptorTypes.resize(5);
	config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[3] = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	config->descriptorTypes[4] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorStages.resize(5);
	config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[3] = VK_SHADER_STAGE_VERTEX_BIT;
	config->descriptorStages[4] = VK_SHADER_STAGE_FRAGMENT_BIT;

	config->depthTestEnable = VK_TRUE;
	config->cullMode = VK_CULL_MODE_BACK_BIT;
	config->extent = extent;

	return config;
}


GEPipelineConfig* GEScene::createPipelineConfigAnimatedLine(VkExtent2D extent)
{
	GEPipelineConfig* config = new GEPipelineConfig();
	config->vertex_shader = IDR_HTML3;
	config->fragment_shader = IDR_HTML4;

	config->attrStride = sizeof(GEVertexAnimated);
	config->attrOffsets.resize(5);
	config->attrOffsets[0] = offsetof(GEVertexAnimated, pos);
	config->attrOffsets[1] = offsetof(GEVertexAnimated, norm);
	config->attrOffsets[2] = offsetof(GEVertexAnimated, tex);
	config->attrOffsets[3] = offsetof(GEVertexAnimated, weights);
	config->attrOffsets[4] = offsetof(GEVertexAnimated, indices);
	config->attrFormats.resize(5);
	config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;
	config->attrFormats[2] = VK_FORMAT_R32G32_SFLOAT;
	config->attrFormats[3] = VK_FORMAT_R32G32B32A32_SFLOAT;
	config->attrFormats[4] = VK_FORMAT_R32G32B32A32_SINT;


	config->descriptorTypes.resize(5);
	config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	config->descriptorTypes[3] = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	config->descriptorTypes[4] = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	config->descriptorStages.resize(5);
	config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
	config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;
	config->descriptorStages[3] = VK_SHADER_STAGE_VERTEX_BIT;
	config->descriptorStages[4] = VK_SHADER_STAGE_FRAGMENT_BIT;

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
		//esqueletoFill->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
		esqueletoLine->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}
	
	rc->setActivePipeline(ANIMATED_PIPELINE);
	rc->insertPipelineCommands(cc->commandBuffers);
	for (int i = 0; i < cc->commandBuffers.size(); i++)
	{
		cilindroFill->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}

	rc->setActivePipeline(ANIMATED_LINE_PIPELINE);
	rc->insertPipelineCommands(cc->commandBuffers);
	for (int i = 0; i < cc->commandBuffers.size(); i++)
	{
		cilindroLine->addCommands(cc->commandBuffers[i], rc->getActivePipelineLayout(), i);
	}
	
	rc->insertEndCommands(cc->commandBuffers);
	cc->endCommandBuffers();
}