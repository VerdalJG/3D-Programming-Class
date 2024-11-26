#include "Model.h"
#include "Mesh.h"
#include "State.h"
#include "../glm/gtc/matrix_transform.hpp"

#include "../glm/gtc/matrix_transform.hpp"


Model::Model(const SharedPtr<Mesh>& mesh) :
	mesh(mesh)
{
}

void Model::Tick(float deltaTime)
{
	Entity::Tick(deltaTime);

	rotation.y += 32.0f * deltaTime;
	//rotation.x += 32.0f * deltaTime; // For seeing the bottom
	if (rotation.y >= 360.0f)
	{
		rotation.y -= 360.0f;
	}
	if (rotation.x >= 360.0f)
	{
		rotation.x -= 360.0f;
	}
}

void Model::Draw()
{
	Entity::Draw(); // Call base class

	State::modelMatrix = glm::mat4(1.0f);
	
	// Apply translation rotation and scale
	State::modelMatrix = glm::translate(State::modelMatrix, position);

	State::modelMatrix = glm::rotate(State::modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	State::modelMatrix = glm::rotate(State::modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	State::modelMatrix = glm::rotate(State::modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	State::modelMatrix = glm::scale(State::modelMatrix, scale);

	mesh->Draw();
}
