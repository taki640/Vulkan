#pragma once

#include "Base.hpp"

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoord;

	static VkVertexInputBindingDescription GetBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions();
};
