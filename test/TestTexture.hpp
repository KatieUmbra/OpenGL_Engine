#include "Test.hpp"
#include <array>

#define GLFW_INCLUDE_NONE
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

namespace gl::test
{
class texture : public test
{
	float low_bound_1, upper_bound_1;
	float low_bound_2, upper_bound_2;
	std::array<float, 40> positions;
	std::array<unsigned int, 12> indices;
	vertex_array vao;
	vertex_buffer vbo;
	index_buffer ibo;
	buffer_layout blo;
	shader shader;
	gl::texture tex;
	gl::renderer& renderer;
	glm::vec3 translationA;
	glm::vec3 translationB;

public:
	texture(gl::renderer& renderer);
	~texture();

	void on_update(float delta_time) override;
	void on_render() override;
	void on_imgui_render() override;
	bool operator==(const test& other) override;
	std::string get_name() const override;
};
} // namespace gl::test
