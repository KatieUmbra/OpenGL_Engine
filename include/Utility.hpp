#pragma once

#define GLFW_INCLUDE_NONE
#include <string>

namespace gl
{
auto read_file(const std::string& file) -> std::string;
auto get_executable_path() -> std::string;
} // namespace gl
