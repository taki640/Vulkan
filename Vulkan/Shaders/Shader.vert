#version 450

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;

layout(location = 0) out vec3 v_FragColor;
layout(location = 1) out vec2 v_FragTexCoord;

layout(binding = 0) uniform UniformBufferObject {
    mat4 Model;
    mat4 View;
    mat4 Projection;
} ubo;

void main() {
    gl_Position = ubo.Projection * ubo.View * ubo.Model * vec4(a_Position, 0.0, 1.0);
    v_FragColor = a_Color;
    v_FragTexCoord = a_TexCoord;
}