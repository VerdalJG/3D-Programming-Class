#pragma once
#include "GlobalIncludes.h"
#include "../lib/glm/glm.hpp"


class Texture
{
public:
	Texture(uint32_t textureId, glm::ivec2& size);
	~Texture();
	static SharedPtr<Texture> Load(const char* fileName);
	void Bind() const;

private:
	uint32_t textureId;
	glm::ivec2 size;

public:
	uint32_t GetTextureId() const { return textureId; }
	const glm::ivec2& GetSize() const { return size; }
};

