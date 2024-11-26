#pragma once

#include "GlobalIncludes.h"
#include "../lib/glm/mat4x4.hpp"

class Shader
{
public:
	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	~Shader();

	// Gets the OpenGL identifier of the program
	uint32_t GetId() const;

	// Gets the error generated when compiling or linking
	const char* GetError() const;

	// Activates the use of the program
	void Use() const;

	// Activates the writing of attribute type variables and specifies their formats
	void SetupAttributes() const;


	int GetLocation(const char* variableName) const;

	// Set value of uniform variables
	void SetInt(int location, int value);
	void SetFloat(int location, float value);
	void SetVec3(int location, const glm::vec3& vector);
	void SetVec4(int location, const glm::vec4& vector);
	void SetMatrix(int location, const glm::mat4& matrix);

private:
	uint32_t programId;

	void CompileShader(uint32_t shaderId, const std::string& shaderCode);
	void LinkProgram();
	std::vector<int> GetAttributeLocations();
};

