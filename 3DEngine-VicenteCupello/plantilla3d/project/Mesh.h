#pragma once
#include "GlobalIncludes.h"

class Buffer;
class Material;

class Mesh
{
public:
	void AddBuffer(const SharedPtr<Buffer>& buffer, const Material& material);
	void Draw();

private: 
	std::vector<std::pair<SharedPtr<Buffer>, SharedPtr<Material>>> meshBuffers;

public:
	size_t GetNumBuffers() const { return meshBuffers.size(); }
	const SharedPtr<Buffer>& GetBuffer(size_t index) { return meshBuffers[index].first; }

	const Material& GetMaterial(size_t index) const { return *meshBuffers[index].second.get(); }
	Material& GetMaterial(size_t index) { return *meshBuffers[index].second.get(); }
};

