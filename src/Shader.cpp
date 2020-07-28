#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Constructor
Shader::Shader(const char* shaderPath, unsigned int type) : m_ShaderPath(shaderPath){
    // Get Source Code
    std::string shaderCode;
    std::ifstream shaderFile;
    // Allow ifstream exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // Try to ready file
    try{
        // Open
        shaderFile.open(m_ShaderPath);
        // Stringstream
        std::stringstream shaderStream;
        // Read into stream
        shaderStream << shaderFile.rdbuf();
        // Close file
        shaderFile.close();
        // Convert stream to string
        shaderCode = shaderStream.str();
    }
    // Error Catching
    catch(std::ifstream::failure e){
        std::cerr << "Error! Shader file " << m_ShaderPath << " failed to read! Current path: " << std::endl;
    }
    // Get C string
    m_ShaderCode = shaderCode.c_str();
    
    // Create shader
    m_Shader = glCreateShader(type);

    // Attach shader source
    glShaderSource(m_Shader, 1, &m_ShaderCode, NULL);

    // Compile shader
    glCompileShader(m_Shader);

    // Check for compilation success
    int success;
    char info[512];
    glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(m_Shader, 512, NULL, info);
        // Print code
        std::cerr << m_ShaderPath << std::endl;
        std::cerr << "Error! Shader failed to compile! Error:\n" << info << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Destructor
Shader::~Shader(){
    // Delete shader
    glDeleteShader(m_Shader);
}