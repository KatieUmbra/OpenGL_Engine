#pragma once

#define GLFW_INCLUDE_NONE
#include <Utility.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <unordered_map>

namespace gl
{
class shader
{
	unsigned int m_renderer_id;
	std::string m_vs_file_path;
	std::string m_fs_file_path;
	std::unordered_map<std::string, int> m_uniform_location_cache;

	auto get_uniform_location(const std::string& name) -> unsigned int;
	[[nodiscard]] static auto create_shader(const std::string& vertex_shader_file,
											const std::string& fragment_shader_file) -> unsigned int;
	[[nodiscard]] static auto compile_shader(const std::string& source, unsigned int type) -> unsigned int;

public:
	shader(const std::string& vs_path, const std::string& fs_path);
	~shader();

	void bind() const;
	void unbind() const;

	void setUniformVecf4(const std::string& name, glm::vec4 data);
	void setUniformVecf3(const std::string& name, glm::vec3 data);

	void setUniformMatf4(const std::string& name, const glm::mat4& data);

	void setUniformInt1(const std::string& name, int data);
};
} // namespace gl
