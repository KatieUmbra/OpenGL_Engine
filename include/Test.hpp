#pragma once
#define GLFW_INCLUDE_NONE
#include <string>
#include <vector>

namespace gl::test
{
class test
{
public:
	test()
	{
	}
	virtual ~test()
	{
	}
	virtual void on_update(float delta_time)
	{
	}
	virtual void on_render()
	{
	}
	virtual void on_imgui_render()
	{
	}
	virtual bool operator==(const test& other)
	{
		return false;
	}
	virtual std::string get_name() const
	{
		return "";
	}
};

inline std::vector<std::reference_wrapper<test>> registered_tests;

inline void register_test(test& test)
{
	registered_tests.emplace_back(test);
}
} // namespace gl::test
