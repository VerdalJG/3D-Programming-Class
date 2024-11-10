#pragma once

#include <array>
#include <vector>
#include <GL/glew.h>
#include "Shader.h"
#include "Vertex.h"

// Notes:
// Vertex Array Object (VAO) // Stores the state of the vertex attributes and binds them to the shaders.
// Vertex Buffer Object (VBO) // Stores the vertex data (positions, colors) that will be used in rendering. 
// Index Buffer Object (iBO)  // It stores the index data, allowing efficient reuse of vertex data.

class Buffer
{
public:
    Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
    ~Buffer();

    void Draw(const Shader& shader) const;

private:
    GLuint VAO;  // Vertex Array Object
    GLuint VBO;  // Vertex Buffer Object
    GLuint IBO;  // Index Buffer Object (optional, used if indices are provided)

    bool hasIndices;  // To check if an IBO is needed
    size_t indexCount;
};

