#pragma once

#include "Base.hpp"

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec2 Position;
	glm::vec3 Color;

	static VkVertexInputBindingDescription GetBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();
};
