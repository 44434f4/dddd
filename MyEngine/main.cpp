#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/Core/Application.h"
#include "src/Graphics/Renderer.h"

int main() {
	Application::initialize(800, 600);
	Application::Run();
		

}