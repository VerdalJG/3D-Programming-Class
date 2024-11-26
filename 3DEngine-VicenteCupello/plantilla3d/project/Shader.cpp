#include "Shader.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>

#include "../glm/gtc/type_ptr.hpp" // For converting glm matrices to pointer format for OpenGL
#include "Vertex.h"
#include "GL/glew.h"               // GLEW for loading OpenGL functions

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
{
	// Create and compile the vertex shader
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(vertexShader, vertexCode);   

    // Create and compile the fragment shader
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader(fragmentShader, fragmentCode);                  

    // Create the shader program and attach the compiled shaders
    programId = glCreateProgram();               
    glAttachShader(programId, vertexShader);      
    glAttachShader(programId, fragmentShader);   
    LinkProgram();                                

    // Clean up by deleting the shaders after linking, as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
    glDeleteProgram(programId); // Cleans up the shader program
}

uint32_t Shader::GetId() const
{
	return programId;
}

const char* Shader::GetError() const
{
    const unsigned int bufferSize = 1024;
    static char errorLog[bufferSize]; // Static buffer to hold the error log
    glGetProgramInfoLog(GetId(), bufferSize, nullptr, errorLog); // Get the error log from OpenGL
    return errorLog; // Return the error log
}

void Shader::Use() const
{
    glUseProgram(programId);
}

void Shader::SetupAttributes() const
{
    int vertexPositionLocation = glGetAttribLocation(programId, "vpos"); // vpos is the name used in the .glsl file, same for vcolor
    if (vertexPositionLocation != -1) // Check if the attribute was found
    {
        glEnableVertexAttribArray(vertexPositionLocation); // Enable the vertex attribute array
        // Define the data layout for the attribute - the 3 implies 3 coordinates (x,y,z), stored as float, should not be normalized
        glVertexAttribPointer(
            vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<const void*>(offsetof(Vertex, position)) // Defines the starting point of where the position attribute is in each vertex
        ); 
    }

    int vertexColorLocation = glGetAttribLocation(programId, "vcolor");
    if (vertexColorLocation != -1)
    {
        glEnableVertexAttribArray(vertexColorLocation);
        glVertexAttribPointer(
            vertexColorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<const void*>(offsetof(Vertex, color))
        );
    }

    int vtextureCoordinatesLocation = glGetAttribLocation(programId, "vtex");
    if (vtextureCoordinatesLocation != -1)
    {
        glEnableVertexAttribArray(vtextureCoordinatesLocation);
        glVertexAttribPointer(
            vtextureCoordinatesLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<const void*>(offsetof(Vertex, coordinates))
        );
    }
}

int Shader::GetLocation(const char* variableName) const
{
    return glGetUniformLocation(programId, variableName);
}

void Shader::SetInt(int location, int value)
{
    if (location != -1)
    {
        glUniform1i(location, value);
    }
}

void Shader::SetFloat(int location, float value)
{
    if (location != -1)
    {
        glUniform1f(location, value);
    }
}

void Shader::SetVec3(int location, const glm::vec3& vector)
{
    if (location != -1)
    {
        glUniform3f(location, vector.x, vector.y, vector.z);
    }
}

void Shader::SetVec4(int location, const glm::vec4& vector)
{
    if (location != -1)
    {
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }
}

void Shader::SetMatrix(int location, const glm::mat4& matrix)
{
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void Shader::CompileShader(uint32_t shaderId, const std::string& shaderCode)
{
    const char* code = shaderCode.c_str(); // Store in a c style string

    // The 1 indicates that there is only one string to set
    // nullptr means to use the null terminator to know when the string ends
    glShaderSource(shaderId, 1, &code, nullptr); 
    glCompileShader(shaderId);

    // Check for success
    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        printf("ERROR - Compilation failed. Log: \n%s\n", infoLog);
    }
}

void Shader::LinkProgram()
{
    glLinkProgram(programId); // Links shaders (vertex, fragment, etc.)]

    int success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        printf("ERROR - Linking failed. Log: \n%s\n", infoLog);
    }
}

std::vector<int> Shader::GetAttributeLocations()
{
    std::vector<int> attributeLocations;

    // Get location for vertex position
    int vertexPositionLocation = glGetAttribLocation(programId, "vpos");
    if (vertexPositionLocation != -1)
    {
        attributeLocations.push_back(vertexPositionLocation);
    }
    else
    {
        attributeLocations.push_back(-1); // -1 if location not found
    }

    // Get location for vertex clearColor
    int vertexColorLocation = glGetAttribLocation(programId, "vcolor");
    if (vertexColorLocation != -1)
    {
        attributeLocations.push_back(vertexColorLocation);
    }
    else
    {
        attributeLocations.push_back(-1); // -1 if location not found
    }

    // We can add more attributes in a similar way if needed

    return attributeLocations;
}