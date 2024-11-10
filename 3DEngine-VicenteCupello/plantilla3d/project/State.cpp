#include "State.h"
#include "Shader.h"

// Need to define static variables in .cpp
SharedPtr<Shader> State::defaultShader = nullptr;
glm::mat4 State::projectionMatrix = glm::mat4(1.0f);
glm::mat4 State::viewMatrix = glm::mat4(1.0f);
glm::mat4 State::modelMatrix = glm::mat4(1.0f);