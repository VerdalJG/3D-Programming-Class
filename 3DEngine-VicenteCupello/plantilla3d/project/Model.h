#pragma once
#include "GlobalIncludes.h"
#include "Entity.h"

class Mesh;

class Model : public Entity
{
public:
    Model(const SharedPtr<Mesh>& mesh);

    virtual void Tick(float deltaTime) override;
    virtual void Draw() override;

private:
    SharedPtr<Mesh> mesh;
};

