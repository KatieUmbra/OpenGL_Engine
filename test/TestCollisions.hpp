#pragma once

#define GLFW_INCLUDE_NONE
#include "Renderer.hpp"
#include "Test.hpp"
#include <glm/ext/vector_float2.hpp>
#include <memory>

namespace gl::test
{
using color3 = glm::vec3;
class player
{
	glm::vec2 acceleration;
	glm::vec2 velocity;
	glm::vec2 position;

	gl::test::color3 color;
	float drag;
	float accel;
	unsigned int box_size;
	std::unique_ptr<player> future;

public:
	player(bool make_future);
	~player();

	void update();
	void render();
	std::unique_ptr<player>& peek();
};
class map
{
	std::array<std::array<short, 8>, 8> tiles;
	unsigned int height;
	unsigned int width;
	unsigned int box_size;

public:
	map(std::array<std::array<short, 8>, 8>);
	~map();

	void render();
};
class collisions : public test
{
	player player;
	map map;
	renderer renderer;
	vertex_array vao;
	vertex_buffer vbo;
	index_buffer ibo;
	buffer_layout blo;
	shader shader;

public:
	collisions(gl::renderer& renderer);
	~collisions();

	void on_update(float delta_time) override;
	void on_render() override;
	void on_imgui_render() override;
	bool operator==(const test& other) override;
	std::string get_name() const override;
};
}; // namespace gl::test
