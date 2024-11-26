#pragma once

#include "../lib/glm/vec3.hpp"

struct Vertex
{
	Vertex(const glm::vec3& position, const glm::vec3& color, const glm::vec2& coordinates) :
		position(position),
		color(color),
		coordinates(coordinates)
	{
	}

	// Vertex position
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 coordinates;
};