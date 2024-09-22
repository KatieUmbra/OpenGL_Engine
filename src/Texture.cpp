
#include "Utility.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Assert.hpp"
#include "Texture.hpp"
#include "glad/glad.h"

gl::texture::texture(const std::string& path)
	: m_renderer_id{0}, m_file_path{path}, m_local_buffer{nullptr}, m_width{0}, m_height{0}, m_pixel_size{0}
{
	stbi_set_flip_vertically_on_load(1);
	auto real_path = get_executable_path() + "/assets/" + path;
	m_local_buffer = stbi_load(real_path.c_str(), &this->m_width, &this->m_height, &this->m_pixel_size, 4);

	GL_CALL(glGenTextures(1, &this->m_renderer_id));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));
	this->unbind();

	if (m_local_buffer)
	{
		stbi_image_free(m_local_buffer);
	}
}

gl::texture::~texture()
{
	GL_CALL(glDeleteTextures(1, &m_renderer_id));
}

void gl::texture::bind(unsigned int slot) const
{
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void gl::texture::unbind() const
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
