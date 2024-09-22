#include "Utility.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

auto gl::read_file(const std::string& file) -> std::string
{
	auto global_path = get_executable_path();
	auto shader_path = global_path + "/shaders/";
	std::cout << "[OpenGL][INFO]: Shader path '" << shader_path << "' \n";
	std::string path{shader_path + file};
	std::ifstream fs{path};
	std::string shader;
	shader.assign((std::istreambuf_iterator<char>(fs)), (std::istreambuf_iterator<char>()));
	return shader;
}

auto gl::get_executable_path() -> std::string
{
#ifdef _DEBUG
	auto path = std::filesystem::canonical("/proc/self/exe").parent_path().parent_path();
#else
	auto path = std::filesystem::canonical("/proc/self/exe").parent_path();
#endif
	return path.string();
}
