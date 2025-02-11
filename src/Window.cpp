#define GLFW_INCLUDE_NONE
#include "Window.hpp"
#include "Assert.hpp"

#include <exception>
#include <iostream>

namespace gl
{
window::window(const window_properties& props) : m_window{glfw::Window{props.width, props.height, props.title}}
{
	props.hints.apply();
	glfw::makeContextCurrent(this->m_window);
	if (props.vsync)
		glfw::swapInterval(1);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD" << '\n';
		std::terminate();
	}
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_CALL(glEnable(GL_BLEND))
}

window::~window() = default;

bool window::loop() const
{
	return !this->m_window.shouldClose();
}

void window::set_icon(const std::vector<glfw::Image>& imgs)
{
	this->m_window.setIcon(imgs);
}
} // namespace gl
