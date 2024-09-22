#pragma once

#define GLFW_INCLUDE_NONE
namespace gl
{
class vertex_buffer
{
	unsigned int m_renderer_id;

public:
	vertex_buffer(const void* data, unsigned int size);
	~vertex_buffer();

	auto bind() const -> void;
	auto unbind() const -> void;
};
} // namespace gl
