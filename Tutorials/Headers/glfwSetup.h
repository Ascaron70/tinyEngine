#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

class GlfwSetup {
public:
	GlfwSetup();
	~GlfwSetup();

public:
	void renderLoop();

private:
	GLFWwindow* m_window = nullptr;

	const unsigned int SCREEN_WIDTH;
	const unsigned int SCREEN_HEIGHT;

	// Shader variables
	const char* vertexShaderSource;
	const char* fragmentShaderSource;


	int vertexShader;
	int fragmentShader;
	int shaderProgram;

	int ShadersSuccess;
	char ShaderCompileInfoLog[512];

	unsigned int VBO;
	unsigned int VAO;
};