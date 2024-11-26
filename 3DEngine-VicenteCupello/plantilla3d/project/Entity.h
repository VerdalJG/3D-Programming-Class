#pragma once
#include "../lib/glm/glm.hpp"

class Entity
{
public: 
	Entity();
	virtual ~Entity() {}

	void Move(const glm::vec3& vector);

	virtual void Tick(float deltaTime) {}
	virtual void Draw() {}
	

protected:
	glm::vec3 position;
	glm::vec3 rotation; // Rotation values are in degrees
	glm::vec3 scale;

public:
	const glm::vec3& GetPosition() const { return position; }
	void SetPosition(const glm::vec3& newPosition) { position = newPosition; }

	const glm::vec3& GetRotation() const { return rotation; } 
	void SetRotation(const glm::vec3& newRotation) { rotation = newRotation; } 

	const glm::vec3& GetScale() const { return scale; }
	void SetScale(const glm::vec3& newScale) { scale = newScale; }
};

