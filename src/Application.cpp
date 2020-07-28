#include "Application.h"

// GLFW Error Callback Function
void GLFWErrorCallback(int error, const char* description){
	std::cerr << "Error: " << description << std::endl;
}

// Framebuffer size callback function
void FramebufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

// Constructor
Application::Application(int width, int height, const char* title){
	// Initialise GLFW
	std::cout << "Initialising application " << title << std::endl;
	if(!glfwInit()){
		std::cerr << "Error! Unable to initialise GLFW!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set GLFW callback
	glfwSetErrorCallback(GLFWErrorCallback);

	// Initialise window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(!m_Window){
		std::cerr << "Error! Unable to create window!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set OpenGL context
	glfwMakeContextCurrent(m_Window);

	// Set Framebuffer resize callback
	glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

	// Initialise glad
	if (!gladLoadGL()){
		std::cerr << "Error! Unable to load GLAD!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set Clear Colour
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	const std::vector<Vertex> vertices1 = {
        // positions         // colors
        {{1.0f, -0.5f, 0.0f},  {1.0f, 0.0f, 0.0f, 1.0f}},  // bottom right
        {{0.5f, -0.5f, 0.0f},  {0.0f, 1.0f, 0.0f, 1.0f}},  // bottom left
        {{0.5f,  0.5f, 0.0f},  {0.0f, 0.0f, 1.0f, 1.0f}}   // top 
    };

    std::vector<unsigned int> indices1 = {
        0, 1, 2
    };

	std::vector<Vertex> vertices2 = {
        {{-0.5f, -0.5f, 0.0f}, {0.5f, 0.44f, 0.8f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.5f, 0.44f, 0.8f, 1.0f}},
        {{0.0f, 0.5f, 0.0f}, {0.2f, 0.76f, 0.3f, 1.0f}},
		{{0.0f, 0.0f, 0.0f}, {0.2f, 0.76f, 0.3f, 1.0f}}
    };
    std::vector<unsigned int> indices2 = {
        0, 1, 2,
		2, 3, 0
    };
	
	// Vertex shader
	Shader vertexShader("../src/shaders/test.vert", GL_VERTEX_SHADER);
    
	// Frag shader
	Shader fragShader("../src/shaders/test.frag", GL_FRAGMENT_SHADER);

	// Generate VAO
	glGenVertexArrays(1, &m_VAO);

	// Bind VAO
	glBindVertexArray(m_VAO);

	// Add 2 models
	AddModel(vertices1, indices1, vertexShader, fragShader);
	AddModel(vertices2, indices2, vertexShader, fragShader);
}

// Destructor
Application::~Application(){
	// Message
	std::cout << "Exiting..." << std::endl;

	// Destroy window
	glfwDestroyWindow(m_Window);

	// Terminate GLFW
	glfwTerminate();
}

// Run application
void Application::Run(){
	// Main loop
	while(!glfwWindowShouldClose(m_Window)){
		// Handle Input
		HandleInput();
		
		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw
		Draw();

		// Polling and Buffer Swap
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

// Draw Call
void Application::Draw(){
	// Bind VAO
	glBindVertexArray(m_VAO);
	
	// Draw models
	for (const auto& model : m_Models){
		model->Draw();
	}
}

// Handle All Inputs
void Application::HandleInput(){
	// Check for escape key
	if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(m_Window, true);
	}
}

void Application::AddModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader vertexShader, Shader fragmentShader){
	m_Models.push_back(std::make_unique<Model>(vertices, indices, vertexShader, fragmentShader));
}