#pragma once

#define GLFW_INCLUDE_NONE
#include <exception>
#include <vector>

#include "glad/glad.h"

namespace gl
{
struct buffer_element
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static auto get_size_of_type(unsigned int type) -> unsigned int
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			return 0;
		}
	}
};
class buffer_layout
{
	std::vector<buffer_element> m_elements;
	unsigned int m_stride;

public:
#define PUSH(TYPE, GL_TYPE, NORMALIZE)                                                                                 \
	template <> void push<TYPE>(unsigned int count)                                                                    \
	{                                                                                                                  \
		this->m_elements.emplace_back(buffer_element{GL_TYPE, count, NORMALIZE});                                      \
		this->m_stride += buffer_element::get_size_of_type(GL_TYPE) * count;                                           \
	}

	template <typename T> void push(unsigned int count)
	{
		std::terminate();
	}

	PUSH(float, GL_FLOAT, false);
	PUSH(unsigned int, GL_UNSIGNED_INT, false);
	PUSH(unsigned char, GL_UNSIGNED_BYTE, true);

	auto get_elements() const -> const std::vector<buffer_element>&
	{
		return this->m_elements;
	}

	auto get_stride() const -> unsigned int
	{
		return this->m_stride;
	}
};
} // namespace gl
