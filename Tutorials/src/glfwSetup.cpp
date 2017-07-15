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

GlfwSetup::GlfwSetup() 
{
	LogStart("Constructor : glfwSetup");

	Check(glfwInit(), "glfwInit() : [ GL_TRUE ]", "glfwinit() : [ GL_FALSE ]"); // init the glfw library

	//manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL functions
	//Check(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "GLAD Initialized", "Failed To Initialize GLAD");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						Log("glfw WindowHints : [ MAJOR : 3 ]");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						Log("glfw WindowHints : [ MINOR : 3 ]");
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);							Log("glfw WindowHints : [ RESIZABLE : [ GL_TRUE ] ]");
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		Log("glfw WindowHints : [ CORE_PROFILE ]\n");
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				//Log("glfw WindowHints : [ FORWARD_COMPAT ]");  // this is for mac users

	//create the window
	this->m_window = glfwCreateWindow(1024, (1024 / 16 * 9), "Learn OpenGL", NULL, NULL);
	CompareToNULL(this->m_window, "Window Created\n", "Failed to create a window\n", glfwTerminate());

	// make our window the current context
	glfwMakeContextCurrent(this->m_window);								LogSet("Context");

	// outputs openGL related errors to the console
	glfwSetErrorCallback(&LogGlfwError);								LogSet("Error Callback");
	
	//this handles resizing of the window
	glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

	LogEnd("[ Constructor : glfwSetup ]");
}

GlfwSetup::~GlfwSetup() 
{
	LogStart("[ DeConstructor : glfwSetup ]");
		glfwTerminate();			Log("glfw [ TERMINATED ]");
	LogEnd("[ DeConstructor : glfwSetup ]");
	cin.get();
}

void GlfwSetup::renderLoop()
{
	LogStart("Render Loop");

	while (!glfwWindowShouldClose(this->m_window))
	{

		//handle input every frame
		processInput(this->m_window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);			// set the color
		glClear(GL_COLOR_BUFFER_BIT);					// clear the screen with the color set with glClearColor(r, g, b, a)

		glfwSwapBuffers(this->m_window);
		glfwPollEvents();

	}

	LogEnd("Render Loop");
}