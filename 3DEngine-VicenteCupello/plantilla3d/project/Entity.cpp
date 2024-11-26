#include "Entity.h"

Entity::Entity() :
	position(0.0f),
	rotation(0.0f),
	scale(1.0f)
{
}

void Entity::Move(const glm::vec3& vector)
{
	position += vector;
}
