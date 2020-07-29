#include "ShaderProgram.h"

#include "glm/trigonometric.hpp"

// Constructor
ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader):
m_VertexShader(std::make_unique<Shader>(vertexShader)),
m_FragmentShader(std::make_unique<Shader>(fragmentShader))
{
	// Create shader program
	m_ShaderProgram = glCreateProgram();

	// Attach shaders
	glAttachShader(m_ShaderProgram, m_VertexShader->GetShader());
	glAttachShader(m_ShaderProgram, m_FragmentShader->GetShader());
	glLinkProgram(m_ShaderProgram);

	// Check if shader program was created successfully
	int success;
    char info[512];
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, info);
		std::cerr << "Error! Unable to link shader program! Error:\n" << info << std::endl;
		exit(EXIT_FAILURE);
	}
}

// Destructor
ShaderProgram::~ShaderProgram(){
	// Delete Shader Program
	glDeleteProgram(m_ShaderProgram);
}

// Use Shader Program
void ShaderProgram::Bind(){
	// Use shader program
	glUseProgram(m_ShaderProgram);
}