#pragma once
#include "Resources/ResourceBase.hpp"

#include "Resources/Shader/Shader.hpp"


namespace TwilliEngine
{

class ShaderProgram : public ResourceBase<ShaderProgram>
{
public:
    ShaderProgram() {}
    ShaderProgram(const std::string &name) : ResourceBase(name) {}
    ~ShaderProgram() {}
  
    void Build();
    void Bind();

    // TODO:
    void SetConstantBuffers() {}
    // TODO:
    void SetRenderTargetView() {}

    void AttachShader(Shader::Type type, Shader::Key shader);
    Shader::Key GetShader(Shader::Type type) { return mShaders[type]; };

    

private:
    Shader::Key mShaders[Shader::Type::COUNT];
};

}