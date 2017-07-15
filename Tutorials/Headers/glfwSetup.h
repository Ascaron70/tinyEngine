#pragma once

#include "Setup.h"

class GlfwSetup {
public:
	GlfwSetup();
	~GlfwSetup();

public:
	void renderLoop();

private:
	GLFWwindow* m_window = nullptr;
};