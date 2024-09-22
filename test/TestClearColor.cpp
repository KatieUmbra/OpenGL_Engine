#include "TestClearColor.hpp"

#include "Assert.hpp"
#include <imgui.h>

gl::test::clear_color::clear_color() : m_clear_color{1.0f, 0.8f, 0.8f, 1.0f}
{
}

gl::test::clear_color::~clear_color()
{
}

void gl::test::clear_color::on_update(float delta_time)
{
}

void gl::test::clear_color::on_render()
{
	GL_CALL(glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void gl::test::clear_color::on_imgui_render()
{
	ImGui::ColorEdit4("Clear Color", reinterpret_cast<float*>(&m_clear_color));
}

bool gl::test::clear_color::operator==(const test& other)
{
	return this->get_name() == other.get_name();
}

std::string gl::test::clear_color::get_name() const
{
	return "Clear Color";
}
