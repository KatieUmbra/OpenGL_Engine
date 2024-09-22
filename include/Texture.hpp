#pragma once

#define GLFW_INCLUDE_NONE
#include <string>

namespace gl
{
class texture
{
	unsigned int m_renderer_id;
	unsigned char* m_local_buffer;
	std::string m_file_path;
	int m_width, m_height, m_pixel_size;

public:
	texture(const std::string& path);
	~texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline auto get_width() const -> int
	{
		return this->m_width;
	}
	inline auto get_height() const -> int
	{
		return this->m_height;
	}
};
} // namespace gl
