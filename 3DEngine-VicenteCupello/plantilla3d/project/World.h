#pragma once
#include "GlobalIncludes.h"

class Entity;
class Camera;

class World
{
public:
	void AddEntity(const SharedPtr<Entity>& entity);
	void RemoveEntity(const SharedPtr<Entity>& entity);
	void Tick(float deltaTime);
	void Draw();

private:
	std::vector<SharedPtr<Entity>> entities;
	std::vector<SharedPtr<Camera>> cameras;

public:
	const SharedPtr<Entity>& GetEntity(size_t index) const { return entities[index]; }
	SharedPtr<Entity>& GetEntity(size_t index) { return entities[index]; }
};

