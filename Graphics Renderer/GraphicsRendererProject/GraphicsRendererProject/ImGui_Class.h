#pragma once
#include "ImGUI.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void UIRender()
{
	ImGui::Render();

	if (ImGui::GetDrawData())
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

void UINewFrame()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void UIEndFrame()
{
	ImGui::EndFrame();
}

void UIShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}