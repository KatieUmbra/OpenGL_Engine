#pragma once

#define GLFW_INCLUDE_NONE
#include "Test.hpp"
#include <array>

namespace gl::test
{
class clear_color : public test
{
	std::array<float, 4> m_clear_color;

public:
	clear_color();
	~clear_color();

	void on_update(float delta_time) override;
	void on_render() override;
	void on_imgui_render() override;
	bool operator==(const test& other) override;
	std::string get_name() const override;
};
} // namespace gl::test
