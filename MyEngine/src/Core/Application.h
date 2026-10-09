#pragma once
#include "../includes.h"
#include "../Graphics/Renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Application
{
	public:
		static GLFWwindow* window;
		static int initialize(int width, int height);
		static void Run();

	
};

