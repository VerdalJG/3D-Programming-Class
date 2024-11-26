#pragma once
#include "GlobalIncludes.h"
#include "../lib/glm/glm.hpp"

class Shader;

class State
{
public:
	static SharedPtr<Shader> defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;
};

