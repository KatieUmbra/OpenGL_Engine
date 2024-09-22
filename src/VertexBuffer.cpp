#include "VertexBuffer.hpp"
#include "Assert.hpp"

gl::vertex_buffer::vertex_buffer(const void* data, unsigned int size) : m_renderer_id{0}
{
	GL_CALL(glGenBuffers(1, &this->m_renderer_id));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->m_renderer_id));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

gl::vertex_buffer::~vertex_buffer()
{
	GL_CALL(glDeleteBuffers(1, &this->m_renderer_id));
}

auto gl::vertex_buffer::bind() const -> void
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->m_renderer_id));
}

auto gl::vertex_buffer::unbind() const -> void
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
