#pragma once
#include "GlobalIncludes.h"

class Texture;
class Shader;

class Material
{
public:
	Material(const SharedPtr<Texture>& texture = nullptr, const SharedPtr<Shader>& shader = nullptr);
	void Prepare();

private:
	SharedPtr<Texture> texture = nullptr;
	SharedPtr<Shader> shader = nullptr;


public:
	SharedPtr<Shader> GetShader() { return shader; }
	const SharedPtr<Shader> GetShader() const { return shader; }
	void SetShader(const SharedPtr<Shader>& newShader) { shader = newShader; }

	const SharedPtr<Texture> GetTexture() const { return texture; }
	void SetTexture(const SharedPtr<Texture>& newTexture) { texture = newTexture; }
};

