#include "VertexArray.hpp"
#include "Assert.hpp"
#include <cstdint>

gl::vertex_array::vertex_array() : m_renderer_id{0}
{
	GL_CALL(glGenVertexArrays(1, &this->m_renderer_id));
}

gl::vertex_array::~vertex_array()
{
	GL_CALL(glDeleteVertexArrays(1, &this->m_renderer_id));
}

void gl::vertex_array::add_buffer(const vertex_buffer& vb, const buffer_layout& bl)
{
	this->bind();
	vb.bind();
	const auto& elements = bl.get_elements();
	std::uintptr_t offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(glVertexAttribPointer(i, element.count, element.type, (element.normalized ? GL_TRUE : GL_FALSE),
									  bl.get_stride(), reinterpret_cast<const void*>(offset));)
		offset += element.count * buffer_element::get_size_of_type(element.type);
	}
}

void gl::vertex_array::bind() const
{
	GL_CALL(glBindVertexArray(this->m_renderer_id));
}

void gl::vertex_array::unbind() const
{
	GL_CALL(glBindVertexArray(0));
}
