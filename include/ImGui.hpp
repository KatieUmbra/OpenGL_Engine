#pragma once

#define GLFW_INCLUDE_NONE
#include "glfwpp/window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace gl::imgui
{
static inline void cleanup_imgui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

static inline void init_imgui(const glfw::Window& wnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	auto& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	ImGui_ImplGlfw_InitForOpenGL(wnd, true); // Second param install_callback=true will install GLFW
											 // callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

static inline void start_render_imgui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

static inline void end_render_imgui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace gl::imgui
