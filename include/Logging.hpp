#pragma once
#define GLFW_INCLUDE_NONE
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

inline auto setup_logging() -> std::unique_ptr<std::ofstream>
{
	std::string file{_SOLUTIONDIR "/log.txt"};
	std::unique_ptr<std::ofstream> logging_file = std::make_unique<std::ofstream>(file, std::ios::app);
	auto current = std::chrono::system_clock::now();
	std::cerr.rdbuf(logging_file->rdbuf());
	std::cout.rdbuf(logging_file->rdbuf());
	std::cout << std::endl << "===================" << std::endl;
	std::cout << current << std::endl;
	std::cout << "===================" << std::endl;
	return logging_file;
}
