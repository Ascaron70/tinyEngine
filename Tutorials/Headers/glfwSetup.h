#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
using namespace std;

class GlfwSetup {
public:
	GlfwSetup();
	~GlfwSetup();

public:
	void renderLoop();

private:
	GLFWwindow* m_window = nullptr;
};