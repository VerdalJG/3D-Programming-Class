#include "Mesh.h"
#include "Shader.h"
#include "State.h"
#include "Buffer.h"
#include "Material.h"
#include <iostream>

void Mesh::AddBuffer(const SharedPtr<Buffer>& buffer, const Material& material)
{
	meshBuffers.push_back(std::make_pair(buffer, std::make_shared<Material>(material)));
}

void Mesh::Draw()
{
	for (auto& pair : meshBuffers)
	{
		Material* material = pair.second.get();
		if (material)
		{
			pair.second.get()->Prepare();
			pair.first.get()->Draw(*material->GetShader());
		}
	}
}
