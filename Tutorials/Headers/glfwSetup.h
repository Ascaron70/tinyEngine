#pragma once

#include "Shader.h"

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

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	Shader* ourShader;

	unsigned int texture, texture2;

};