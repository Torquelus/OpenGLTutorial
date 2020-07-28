#pragma once

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model.h"
#include "Shader.h"

// Application Class
class Application{
private:
	GLFWwindow* m_Window;									// GLFW Window
	unsigned int m_VAO;										// Vertex Array Object
	std::vector<std::unique_ptr<Model>> m_Models;			// Vector of all models
public:
	Application(int width, int height, const char* title);	// Constructor
	~Application();											// Destructor
	void Run();												// Run Application
	void Draw();											// Draw Call
	void HandleInput();										// Handle All Inputs
	void AddModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader vertexShader, Shader fragmentShader);			// Add Model to Vector of Models
};