#pragma once
#include "../includes.h"
#include "../assets/shaders/shaders.h"

class Renderer
{
public:
	static void InitShader();//тут создаются шейдеры + программа + удаляются шейдеры
	static void InitGeom();// тут создаются VAO и VBO
	static void Draw();//просто объединяющая фигня
	static unsigned int shaderProgram;


private:
	static unsigned int VAO;
	static unsigned int VBO;
};

