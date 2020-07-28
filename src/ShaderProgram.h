#pragma once

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

// Shader Program Class
class ShaderProgram{
private:
	unsigned int m_ShaderProgram;					// Shader Program
	std::unique_ptr<Shader> m_VertexShader;			// Vertex Shader
	std::unique_ptr<Shader> m_FragmentShader;		// Fragment Shader
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);		// Constructor
	~ShaderProgram();	// Destructor
	void Bind();		// Use Shader Program
	void Delete(){
		// Delete Shader Program
		glDeleteProgram(m_ShaderProgram);
	}
};