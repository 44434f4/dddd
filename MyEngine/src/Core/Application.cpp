
#include "Application.h"
#include "../Graphics/Renderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

GLFWwindow* Application::window = nullptr;


int Application::initialize(int width, int height)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    window = glfwCreateWindow(
        width, height,
        "My 2D Engine",
        nullptr, nullptr
    );

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        return -1;
    }

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Инициализация Renderer
    Renderer::InitShader();
    Renderer::InitGeom();

    return 0;
}





void Application::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 1. Начинаем кадр ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiWindowFlags hostFlags =
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpaceHost", nullptr, hostFlags);

        ImGui::PopStyleVar(3);

        ImGui::DockSpace(
            ImGui::GetID("MyDockSpace"),
            ImVec2(0.0f, 0.0f),
            ImGuiDockNodeFlags_PassthruCentralNode
        );

        ImGui::End();

        // 2. Создаём панели
        ImGui::Begin("Scene View");
        ImGui::Text("2D Scene");
        ImGui::End();

        ImGui::Begin("Hierarchy");
        ImGui::Text("Scene");
        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::Text("Object Properties");
        ImGui::End();

        ImGui::Begin("Console");
        ImGui::Text("Engine started!");
        ImGui::End();

        // 3. Очищаем экран
        glClearColor(0.10f, 0.10f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 4. Рисуем треугольник
        Renderer::Draw();

        // 5. Рисуем интерфейс поверх сцены
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );

        // 6. Показываем кадр
        glfwSwapBuffers(window);
    }
}



