#include "Model.h"

#include <iostream>

// Constructor
Model::Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader vertexShader, Shader fragmentShader):
m_Vertices(vertices),
m_Indices(indices),
m_ShaderProgram(std::make_unique<ShaderProgram>(vertexShader, fragmentShader))
{
    // Create EBO
    glGenBuffers(1, &m_EBO);

    // Generate VBO
    glGenBuffers(1, &m_VBO);
}

// Destructor
Model::~Model(){
    // Delete Buffers
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
}

// Bind Model
void Model::Bind(){
    // Bind Shader
    m_ShaderProgram->Bind();

    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    // Transfer indices to EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices[0]) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // Transfer data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices[0]) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
    glEnableVertexAttribArray(1);
}

// Draw Call
void Model::Draw(){    
    // Bind Model
    Bind();

    // OpenGL Draw Call
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}