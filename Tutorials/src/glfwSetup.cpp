#include "../Headers/glfwSetup.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

static void LogGlfwError(int id, const char* description)
{
	cout << "[ GLFW ERROR ] : " << description << " !!!" << endl << endl;
}

GlfwSetup::GlfwSetup() 
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window
	this->m_window = glfwCreateWindow(1024, (1024 / 16 * 9), "Learn OpenGL", NULL, NULL);

	// make our window the current context
	glfwMakeContextCurrent(this->m_window);

	//this handles resizing of the window
	glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	
	// outputs openGL related errors to the console
	glfwSetErrorCallback(&LogGlfwError);
}

GlfwSetup::~GlfwSetup() 
{
	glfwTerminate();
}

void GlfwSetup::renderLoop()
{
	while (!glfwWindowShouldClose(this->m_window))
	{
		//handle input every frame
		processInput(this->m_window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);			// set the color
		glClear(GL_COLOR_BUFFER_BIT);					// clear the screen with the color set with glClearColor(r, g, b, a)

		glfwSwapBuffers(this->m_window);
		glfwPollEvents();
	}
}