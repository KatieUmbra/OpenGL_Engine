#include "ImGui.hpp"
#include "Test.hpp"
#define GLFW_INCLUDE_NONE
#include "Logging.hpp"
#include "TestClearColor.hpp"
#include "TestTexture.hpp"
#include "glfwpp/glfwpp.h"

auto main() -> int
{
	// =======================================================
	//                    Initialization
	// =======================================================
	auto logger = setup_logging();
	[[maybe_unused]] auto library = glfw::init();
	const glfw::WindowHints hints{.resizable = false,
								  .clientApi = glfw::ClientApi::OpenGl,
								  .contextVersionMajor = 4,
								  .contextVersionMinor = 6,
								  .openglProfile = glfw::OpenGlProfile::Core};
	hints.apply();
	const gl::window_properties props{hints, 800, 800, "Hello OpenGL", false, true};
	gl::window window{props};
	gl::imgui::init_imgui(window.get_glfw_window());
	gl::renderer renderer{window};

	// =======================================================
	//                       Testing
	// =======================================================

	gl::test::clear_color clear_test{};
	gl::test::texture texture_test{renderer};
	// gl::test::collisions collisions_test{renderer};

	gl::test::register_test(clear_test);
	gl::test::register_test(texture_test);
	// gl::test::register_test(collisions_test);

	// =======================================================

	auto& tests = gl::test::registered_tests;
	gl::test::test base_reference{};
	std::reference_wrapper<gl::test::test> current_test = base_reference;

	// =======================================================
	//                      Main Loop
	// =======================================================

	while (window.loop())
	{
		renderer.clear();
		if (current_test.get().get_name() != "")
		{
			current_test.get().on_update(0.0f);
			current_test.get().on_render();
		}
		else
		{
			renderer.clear({0.1f, 0.1f, 0.1f, 0.1f});
		}

		gl::imgui::start_render_imgui();
		ImGui::Text("OpenGL Test Application");
		auto framerate = ImGui::GetIO().Framerate;
		ImGui::Text("Framerate %.2f", framerate);
		ImGui::Separator();
		if (current_test.get().get_name() != "")
		{
			ImGui::Text("Test Properties:");
			ImGui::Separator();
			current_test.get().on_imgui_render();
			ImGui::Separator();
			if (ImGui::Button("Back"))
			{
				current_test = base_reference;
			}
		}
		else
		{
			ImGui::Text("Tests Available:");
			ImGui::BeginGroup();
			for (auto& element : tests)
			{
				if (ImGui::Button(element.get().get_name().c_str()))
				{
					current_test = element;
				}
			}
			ImGui::EndGroup();
		}

		gl::imgui::end_render_imgui();
		renderer.update_buffers();
	}
	gl::imgui::cleanup_imgui();
	logger->close();
}
