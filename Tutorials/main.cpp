#include "Headers/glfwSetup.h"

int main() 
{
	LogStart("main()");

		GlfwSetup glfwsetup;
		glfwsetup.renderLoop();

	LogEnd("main()");

	return 0;
}