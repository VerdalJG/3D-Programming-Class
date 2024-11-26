#include "Camera.h"
#include "State.h"

#include "../lib/glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"


void Camera::Prepare()
{
	// Send projection matrix
	State::projectionMatrix = projectionMatrix;

	// Calculate view matrix
	State::viewMatrix = glm::mat4(1.0f);

	// Inverse translation
	State::viewMatrix = glm::translate(State::viewMatrix, -position);

	// Rotation
	State::viewMatrix = glm::rotate(State::viewMatrix, -glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	State::viewMatrix = glm::rotate(State::viewMatrix, -glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	State::viewMatrix = glm::rotate(State::viewMatrix, -glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor(viewport.x, viewport.y, viewport.z, viewport.w);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);
}
