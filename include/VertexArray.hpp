#pragma once

#define GLFW_INCLUDE_NONE
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"

namespace gl
{
class vertex_array
{
	unsigned int m_renderer_id;

public:
	vertex_array();
	~vertex_array();

	void add_buffer(const vertex_buffer& vb, const buffer_layout& bl);
	void bind() const;
	void unbind() const;
};
} // namespace gl
