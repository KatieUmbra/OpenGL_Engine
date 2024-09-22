#pragma once

#define GLFW_INCLUDE_NONE
#include "glfwpp/window.h"
#include <glm/ext/vector_float4.hpp>

namespace gl
{
struct window_properties
{
	const glfw::WindowHints& hints;
	unsigned short width, height;
	const char* title;
	bool vsync;
	bool fullscreen;
};
class window
{
	glfw::Window m_window;

public:
	window(const window_properties& props);
	~window();
	bool loop() const;
	void set_icon(const std::vector<glfw::Image>& imgs);
	inline auto get_glfw_window() -> glfw::Window&
	{
		return this->m_window;
	}
};
} // namespace gl
