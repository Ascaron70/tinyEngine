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
	
	// outputs openGL related errors to the console
	glfwSetErrorCallback(&LogGlfwError);

	//SHADERS

	// vertex shader program
	vertexShaderSource =			"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"layout (location = 1) in vec3 aColor;\n"
									"out vec3 ourColor;\n"
									"void main()\n"
									"{\n"
										"gl_Position = vec4(aPos, 1.0);\n"
										"ourColor = aColor;\n"
									"}\0";


	fragmentShaderSource =			"#version 330 core\n"
									"out vec4 FragColor;\n"
									"in vec3 ourColor;\n"
									"void main()\n"
									"{\n"
										"FragColor = vec4(ourColor, 1.0);\n"
									"}\0";

	//create the Vertex Shader and compile
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ShadersSuccess);
	if (!ShadersSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, ShaderCompileInfoLog);
		cout << ShaderCompileInfoLog << endl << endl;
	}

	//create the Fragment Shader and compile
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ShadersSuccess);
	if (!ShadersSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, ShaderCompileInfoLog);
		cout << ShaderCompileInfoLog << endl << endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ShadersSuccess);
	if (!ShadersSuccess)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, ShaderCompileInfoLog);
		cout << ShaderCompileInfoLog << endl << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float triangleOne[] =
	{	// position					//color
		-0.01f, -0.95f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.9f, -0.9f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.9f, 0.9f, 0.0f,		0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //position Attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //color Attribute
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

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
	while (!glfwWindowShouldClose(this->m_window))
	{
		//handle input every frame
		processInput(this->m_window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);			// set the color
		glClear(GL_COLOR_BUFFER_BIT);					// clear the screen with the color set with glClearColor(r, g, b, a)

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(this->m_window);
		glfwPollEvents();
	}
}