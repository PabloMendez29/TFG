#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "GEValidationLayer.h"

//
// CLASE: GEGraphicsContext
//
// DESCRIPCIÓN: Clase que almacena el contexto gráfico de vulkan (instancia y dispositivo)
//
class GEGraphicsContext
{
public:
	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	uint32_t graphicsQueueFamilyIndex;
	uint32_t presentQueueFamilyIndex;

private:
	VkPhysicalDeviceMemoryProperties memProperties;
	GEValidationLayer* validationLayer;

public:
	GEGraphicsContext(GLFWwindow* window);
	~GEGraphicsContext();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkFormat findDepthFormat();

private:
	// Métodos de inicialización de Vulkan
	void createInstance();
	void createValidationLayer();
	void createSurface(GLFWwindow* window);
	void pickPhysicalDevice();
	void createLogicalDevice();

	// Métodos auxiliares
	void showInstanceProperties();
	bool isDeviceSuitable(VkPhysicalDevice pDevice);
	void showDevices();
	void resumeDeviceProperties(VkPhysicalDevice pDevice, int index);
};

