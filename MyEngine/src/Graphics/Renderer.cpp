#include "Renderer.h"


unsigned int Renderer::VAO = 0;
unsigned int Renderer::VBO = 0;
unsigned int Renderer::shaderProgram = 0;

void Renderer::InitShader()
{

    //vertex
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* vertexSource = vert;
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);


    //Fragment
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentSource = frag;
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);



    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

void Renderer::InitGeom()//Spasybo ChatGPT
{
    float vertices[] = {
         0.0f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // location в Vertex Shader
        2,                  // количество координат: X, Y
        GL_FLOAT,           // тип данных
        GL_FALSE,           // не нормализуем
        2 * sizeof(float),  // шаг между вершинами
        (void*)0            // смещение начала данных
    );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::Draw()

{
    std::cout << "Test";
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glUseProgram(0);
}