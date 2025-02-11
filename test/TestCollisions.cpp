#include "TestCollisions.hpp"
#include <imgui.h>
#include <memory>

gl::test::player::player(bool make_future)
	: acceleration{0.0f, 0.0f}, velocity{0.0f, 0.0f}, position{0.0f, 0.0f}, color{1.0f, 1.0f, 1.0f}, drag{5.0f},
	  accel{5.0f}, box_size{200}
{
	if (make_future)
	{
		this->future = std::make_unique<player>(false);
	}
}

gl::test::player::~player()
{
}

gl::test::map::map(std::array<std::array<short, 8>, 8> tiles) : tiles{tiles}
{
}

gl::test::map::~map()
{
}

static std::array<float, 8> corners{100, 100, 200, 100, 200, 200, 100, 200};

static std::array<unsigned int, 6> indices{0, 3, 2, 2, 1, 0};

gl::test::collisions::collisions(gl::renderer& renderer)
	: player{true}, map{{}}, renderer{renderer}, vbo{&corners, 8u * sizeof(float)}, vao{}, blo{},
	  ibo{(const unsigned int*)&indices, 6u}, shader{"CollisionsVert.glsl", "CollisionsFrag.glsl"}
{
	blo.push<float>(2);
	vao.add_buffer(vbo, blo);

	vao.bind();
	ibo.bind();
	vbo.bind();
	shader.bind();

	vao.unbind();
	vbo.unbind();
	ibo.unbind();
	shader.unbind();
}

gl::test::collisions::~collisions()
{
	vao.unbind();
	vbo.unbind();
	ibo.unbind();
	shader.unbind();
}

void gl::test::collisions::on_update(float delta_time)
{
}

void gl::test::collisions::on_render()
{
	shader.bind();
	renderer.draw(vao, ibo, shader);
}

void gl::test::collisions::on_imgui_render()
{
	ImGui::LabelText("", "Collisions Test");
}

bool gl::test::collisions::operator==(const test& other)
{
	return this->get_name() == other.get_name();
}

std::string gl::test::collisions::get_name() const
{
	return "Collisions Test";
}
