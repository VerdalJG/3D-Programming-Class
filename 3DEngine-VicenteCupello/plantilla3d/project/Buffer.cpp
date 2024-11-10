#include "Buffer.h"

Buffer::Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) :
	hasIndices(!indices.empty())
{
    // Generate and bind the VAO to store the vertex attribute state
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the VBO to store vertex data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // If index data is provided, create and bind the IBO
    if (hasIndices)
    {
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    // Unbind VAO and VBO to prevent accidental changes
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    indexCount = indices.size(); // Store the index count for drawing
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &VBO);
    if (hasIndices)
    {
        glDeleteBuffers(1, &IBO);
    }
    glDeleteVertexArrays(1, &VAO);
}

void Buffer::Draw(const Shader& shader) const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    shader.SetupAttributes();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, nullptr);
}
