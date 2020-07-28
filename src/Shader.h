#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Shader class
class Shader{
private:
    const char *m_ShaderPath;                   // Shader path
    const char* m_ShaderCode;
    unsigned int m_Shader;                      // Shader ID
public:
    Shader(const char* shaderPath, unsigned int type);  // Constructor
    ~Shader();                                  // Destructor
    unsigned int GetShader(){
        return m_Shader;
    }
};
