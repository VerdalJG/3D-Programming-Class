#pragma once
#include "GlobalIncludes.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	void Prepare();

private:
	glm::mat4 projectionMatrix;
	glm::ivec4 viewport;
	glm::vec3 clearColor;

public:
	const glm::mat4& GetProjection() const { return projectionMatrix; }
	void SetProjection(const glm::mat4& newProjection) { projectionMatrix = newProjection; }

	const glm::ivec4& GetViewport() const { return viewport; }
	void SetViewport(const glm::ivec4& newViewport) { viewport = newViewport; }

	const glm::vec3& GetClearColor() const { return clearColor; }
	void SetClearColor(const glm::vec3& newColor) { clearColor = newColor; }
};

