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

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR Capabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentModes;
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

	static constexpr std::array<const char*, 1> DEVICE_EXTENSIONS = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	GLFWwindow* m_Window;
	VkInstance m_VkInstance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;	// Implicitly destroyed when the VkInstance is destroyed
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkSurfaceKHR m_Surface;
	VkQueue m_PresentQueue;
	VkSwapchainKHR m_Swapchain;
	std::vector<VkImage> m_SwapchainImages;	// Automatically destroyed by the VkSwapchainKHR
	VkFormat m_SwapchainImageFormat;
	VkExtent2D m_SwapchainExtent;

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

	// Check extension supports
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

	// Swap chain creation
	void CreateSwapChain();
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};