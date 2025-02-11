#include "Shader.hpp"
#include "Assert.hpp"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace gl
{
auto shader::compile_shader(const std::string& source, unsigned int type) -> unsigned int
{
	GL_CALL(unsigned int id = glCreateShader(type))
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, nullptr))
	GL_CALL(glCompileShader(id))

	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
	if (result == GL_FALSE)
	{
		int length;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length))
		char* message = static_cast<char*>(alloca(length * sizeof(char)));
		GL_CALL(glGetShaderInfoLog(id, length, &length, message))
		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << '\n';
		std::cerr << message << '\n';
		GL_CALL(glDeleteShader(id))
		return 0;
	}

	return id;
}

auto shader::create_shader(const std::string& vertex_shader_file,
						   const std::string& fragment_shader_file) -> unsigned int
{
	auto vertex_shader = read_file(vertex_shader_file);

	auto fragment_shader = read_file(fragment_shader_file);

	GL_CALL(auto program = glCreateProgram())
	auto vs = compile_shader(vertex_shader, GL_VERTEX_SHADER);
	auto fs = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

	GL_CALL(glAttachShader(program, vs))
	GL_CALL(glAttachShader(program, fs))
	GL_CALL(glLinkProgram(program))
	GL_CALL(glValidateProgram(program))
	GL_CALL(glDeleteShader(vs))
	GL_CALL(glDeleteShader(fs))

	return program;
}

shader::shader(const std::string& vs_path, const std::string& fs_path)
	: m_fs_file_path{fs_path}, m_vs_file_path{vs_path}, m_renderer_id{0}
{
	this->m_renderer_id = create_shader(vs_path, fs_path);
}

shader::~shader()
{
	GL_CALL(glDeleteProgram(m_renderer_id));
}

void shader::bind() const
{
	GL_CALL(glUseProgram(this->m_renderer_id));
}

void shader::unbind() const
{
	GL_CALL(glUseProgram(0));
}

void shader::setUniformVecf4(const std::string& name, glm::vec4 data)
{
	auto location = this->get_uniform_location(name);
	GL_CALL(glUniform4f(location, data.x, data.y, data.z, data.w));
}

void shader::setUniformVecf3(const std::string& name, glm::vec3 data)
{
	auto location = this->get_uniform_location(name);
	GL_CALL(glUniform3f(location, data.x, data.y, data.z));
}

void shader::setUniformMatf4(const std::string& name, const glm::mat4& data)
{
	auto location = this->get_uniform_location(name);
	GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data)));
}

void shader::setUniformInt1(const std::string& name, int data)
{
	auto location = this->get_uniform_location(name);
	GL_CALL(glUniform1i(location, data));
}

auto shader::get_uniform_location(const std::string& name) -> unsigned int
{
	if (this->m_uniform_location_cache.find(name) != this->m_uniform_location_cache.end())
	{
		return this->m_uniform_location_cache[name];
	}

	GL_CALL(auto location = glGetUniformLocation(this->m_renderer_id, name.c_str()));

	if (location == -1)
	{
		std::cerr << "[WARN]: uniform " << name << " doesn't exist!" << std::endl;
	}

	this->m_uniform_location_cache[name] = location;
	return location;
}
} // namespace gl
