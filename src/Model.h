#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Shader.h"
#include "ShaderProgram.h"

// Struct for vertex
struct Vertex{
    glm::vec3 position;
    glm::vec4 colour;
};

// Class for 3D Model
class Model{
private:
    unsigned int m_VBO;                     // Vertex Buffer Object ID
    unsigned int m_EBO;                     // Element Buffer Object
    std::unique_ptr<ShaderProgram> m_ShaderProgram;          // Shader Program Used to Draw Model
    std::vector<Vertex> m_Vertices;          // Vector of vertices
    std::vector<unsigned int> m_Indices;    // Vector of indices
public:
    Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader vertexShader, Shader fragmentShader);   // Constructor
    ~Model();                               // Destructor
    void Bind();                            // Bind model
    void Draw();                            // Draw Call
    unsigned int Get(){ return m_VBO; }
};