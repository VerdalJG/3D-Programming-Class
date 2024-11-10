#include "Material.h"
#include "Shader.h"
#include "State.h"
#include "Texture.h"

#include "../lib/glm/glm.hpp"

Material::Material(const SharedPtr<Texture>& texture, const SharedPtr<Shader>& shader) : 
	texture(texture)
{
    if (shader)
    {
        this->shader = shader;
    }
    else
    {
        this->shader = State::defaultShader;
    }
}

void Material::Prepare()
{
    shader->Use(); // Important to call first - sets the context for open GL and ensures that modifications apply to this shader

    glm::mat4 mvpMatrix = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
    shader->SetMatrix(shader->GetLocation("mvp"), mvpMatrix);
    if (texture)
    {
        shader->SetInt(shader->GetLocation("texSampler"), 0);
        texture->Bind();
    }
}
