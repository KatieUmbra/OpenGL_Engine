#include "Renderer.hpp"

namespace gl
{
renderer::renderer(window& wd) : m_window{wd}
{
}

void renderer::draw(const vertex_array& vao, index_buffer& ib, const shader& shader)
{
	shader.bind();
	vao.bind();
	ib.bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

void renderer::clear() const
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void renderer::clear(float r, float g, float b, float a) const
{
	this->clear();
	GL_CALL(glClearColor(r, g, b, a));
}

void renderer::clear(glm::vec4 color) const
{
	this->clear();
	GL_CALL(glClearColor(color.x, color.y, color.z, color.w));
}

void renderer::update_buffers()
{
	glfw::pollEvents();
	this->m_window.get_glfw_window().swapBuffers();
}
} // namespace gl
