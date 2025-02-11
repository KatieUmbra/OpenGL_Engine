#pragma once

#define GLFW_INCLUDE_NONE
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Window.hpp"

namespace gl
{
class renderer
{
	window& m_window;

public:
	renderer(window& wd);
	void draw(const vertex_array& vao, index_buffer& ib, const shader& shader);
	void clear() const;
	void clear(float r, float g, float b, float a) const;
	void clear(glm::vec4 color) const;
	void update_buffers();
};
} // namespace gl
