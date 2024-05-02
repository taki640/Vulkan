#pragma once

#include "Base.hpp"

#include "Vertex.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	bool m_FramebufferResized = false;

	void Run();
private:
	static constexpr uint32_t WINDOW_WIDTH = 800;
	static constexpr uint32_t WINDOW_HEIGHT = 600;
#ifdef DEBUG
	static constexpr bool VALIDATION_LAYERS_ENABLED = true;
#else
	static constexpr bool VALIDATION_LAYERS_ENABLED = false;
#endif
	static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
	static constexpr std::array<const char*, 1> VALIDATION_LAYERS = {
		"VK_LAYER_KHRONOS_validation"
	};

	static constexpr std::array<const char*, 1> DEVICE_EXTENSIONS = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<Vertex> TRIANGLE_VERTICES = {
		{ {  0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
		{ {  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
		{ { -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f } }
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
	std::vector<VkImageView> m_SwapchainImageViews;
	VkRenderPass m_RenderPass;
	VkPipelineLayout m_PipelineLayout;
	VkPipeline m_GraphicsPipeline;
	std::vector<VkFramebuffer> m_SwapchainFramebuffers;
	VkCommandPool m_CommandPool;
	std::vector<VkCommandBuffer> m_CommandBuffers;		// Automatically destroyed by the VkCommandPool
	std::vector<VkSemaphore> m_ImageAvailableSemaphores;
	std::vector<VkSemaphore> m_RenderFinishedSemaphores;
	std::vector<VkFence> m_InFlightFences;
	uint32_t m_CurrentFrame = 0;

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
	void RecreateSwapChain();
	void CleanupSwapChain();

	// Image views
	void CreateImageViews();

	// Graphics pipeline
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	// Framebuffers
	void CreateFramebuffers();

	// Command buffers
	void CreateCommandPool();
	void CreateCommandBuffers();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	// DRAWING!!!
	void DrawFrame();
	void CreateSyncObjects();
};