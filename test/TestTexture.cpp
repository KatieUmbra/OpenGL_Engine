#include "TestTexture.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>
#include <string>

static glm::mat4 view = glm::translate(glm::mat4{1.0f}, glm::vec3(0, 0, 0));
static glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);

gl::test::texture::texture(gl::renderer& renderer)
	: low_bound_1(-50.0f), upper_bound_1(50.0f), low_bound_2(100.0f), upper_bound_2(200.0f),
	  positions{
		  low_bound_1,	 low_bound_1,	0.0f, 0.0f, upper_bound_1, low_bound_1,	  1.0f, 0.0f,
		  upper_bound_1, upper_bound_1, 1.0f, 1.0f, low_bound_1,   upper_bound_1, 0.0f, 1.0f,
		  low_bound_2,	 low_bound_2,	0.0f, 0.0f, upper_bound_2, low_bound_2,	  1.0f, 0.0f,
		  upper_bound_2, upper_bound_2, 1.0f, 1.0f, low_bound_2,   upper_bound_2, 0.0f, 1.0f,
	  },
	  indices{0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4}, vao{}, vbo{&positions, 40u * sizeof(float)},
	  ibo{(const unsigned int*)&indices, 12u}, blo{}, shader{"shader.vert", "shader.frag"}, tex{"obama.png"},
	  renderer{renderer}, translationA(200, 200, 0), translationB(400, 200, 0)
{
	blo.push<float>(2);
	blo.push<float>(2);
	vao.add_buffer(vbo, blo);

	vao.bind();
	ibo.bind();
	vbo.bind();
	shader.bind();
	tex.bind();

	shader.setUniformInt1("u_texture", 0);

	vao.unbind();
	vbo.unbind();
	ibo.unbind();
	shader.unbind();
}

gl::test::texture::~texture()
{
	vao.unbind();
	vbo.unbind();
	ibo.unbind();
	shader.unbind();
}

void gl::test::texture::on_update(float delta_time)
{
}
void gl::test::texture::on_render()
{
	shader.bind();
	glm::mat4 model = glm::translate(glm::mat4{1.0f}, translationA);
	glm::mat4 mvp = projection * view * model;
	shader.setUniformMatf4("u_model_view_projection", mvp);
	renderer.draw(vao, ibo, shader);

	model = glm::translate(glm::mat4{1.0f}, translationB);
	mvp = projection * view * model;
	shader.setUniformMatf4("u_model_view_projection", mvp);
	renderer.draw(vao, ibo, shader);
}
void gl::test::texture::on_imgui_render()
{
	ImGui::SliderFloat3("Translate A", &translationA.x, 0.0f, 800.0f);
	ImGui::SliderFloat3("Translate B", &translationB.x, 0.0f, 800.0f);
}

bool gl::test::texture::operator==(const test& other)
{
	return this->get_name() == other.get_name();
}
std::string gl::test::texture::get_name() const
{
	return "Texture Test";
}
