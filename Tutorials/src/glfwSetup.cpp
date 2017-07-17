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
	: SCREEN_WIDTH(1024), 
	  SCREEN_HEIGHT(SCREEN_WIDTH / 16 * 9)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window
	this->m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn OpenGL", NULL, NULL);

	// make our window the current context
	glfwMakeContextCurrent(this->m_window);

	//this handles resizing of the window
	glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		cout << "failed to initialize GLAD" << endl; 
	}
	
	// outputs openGL related errors to the console
	glfwSetErrorCallback(&LogGlfwError);

	ourShader = new Shader("vertexShader.vs", "fragmentShader.fs");

	float triangleOne[] =
	{	// position
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //position Attribute
			glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

GlfwSetup::~GlfwSetup() 
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void GlfwSetup::renderLoop()
{
	float xOffset = 0.0f;
	bool goLeft = false, goRight = true;

	while (!glfwWindowShouldClose(this->m_window))
	{
		//handle input every frame
		processInput(this->m_window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);			// set the color
		glClear(GL_COLOR_BUFFER_BIT);					// clear the screen with the color set with glClearColor(r, g, b, a)

		ourShader->use();

		int offsetLocation = glGetUniformLocation(ourShader->ID, "offset");
		glUniform1f(offsetLocation, xOffset);

		if(goRight) 
		{
			if(xOffset >= 0.5f) 
			{
				goLeft = true;
				goRight = false;
			}
			xOffset += 0.00010;
		}

		if (goLeft)
		{
			if (xOffset <= -0.5f)
			{
				goLeft = false;
				goRight = true;
			}
			xOffset -= 0.00010;
		}

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(this->m_window);
		glfwPollEvents();
	}
}