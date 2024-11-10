#include "World.h"
#include "Camera.h"

void World::AddEntity(const SharedPtr<Entity>& entity)
{
	entities.push_back(entity);
	if (SharedPtr<Camera> newCamera = std::dynamic_pointer_cast<Camera>(entity))
	{
		cameras.push_back(newCamera);
	}
}

void World::RemoveEntity(const SharedPtr<Entity>& entity)
{
	if (entity)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	}
}

void World::Tick(float deltaTime)
{
	for (SharedPtr<Entity> entity : entities)
	{
		entity->Tick(deltaTime);
	}
}

void World::Draw()
{
	for (SharedPtr<Camera> camera : cameras)
	{
		camera->Prepare();
	}

	for (SharedPtr<Entity> entity : entities)
	{
		entity->Draw();
	}
}
