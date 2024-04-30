#pragma once

#include "Base.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> GraphicsFamily;
	std::optional<uint32_t> PresentFamily;

	bool IsComplete() const
	{
		return GraphicsFamily.has_value() && PresentFamily.has_value();
	}
};

class HelloTriangleApp
{
public:
	void Run();
private:
	static constexpr uint32_t WINDOW_WIDTH = 800;
	static constexpr uint32_t WINDOW_HEIGHT = 600;
#ifdef DEBUG
	static constexpr bool VALIDATION_LAYERS_ENABLED = true;
#else
	static constexpr bool VALIDATION_LAYERS_ENABLED = false;
#endif
	static constexpr std::array<const char*, 1> VALIDATION_LAYERS = {
		"VK_LAYER_KHRONOS_validation"
	};

	GLFWwindow* m_Window;
	VkInstance m_VkInstance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;	// Implicitly destroyed when the VkInstance is destroyed
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkSurfaceKHR m_Surface;
	VkQueue m_PresentQueue;

	void InitWindow();
	void InitVulkan();
	void MainLoop();
	void CleanupVulkan();
	void CleanupWindow();

	// Vulkan instance creation
	void CreateVulkanInstance();
	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();

	// Debug messenger creation
	void SetupDebugMessenger();
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	// Create Vulkan surface
	void CreateSurface();

	// Picking a suitable physical device
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	// Logical device
	void CreateLogicalDevice();
};