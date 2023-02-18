#pragma once
#include "Resources/Shader/Shader.hpp"

namespace TwilliEngine
{

class ComputeShader : public Shader, public ResourceBase<ComputeShader>
{
public:
    ComputeShader() : mComputeShader(nullptr) {}
    ComputeShader(std::string_view name) : ResourceBase(name), mComputeShader(nullptr) {}
    ~ComputeShader();

    bool Build(const std::filesystem::path& filepath) override;
    void Bind() override;

//    static ResourceID Create();

private:
    ID3D11ComputeShader *mComputeShader;

};

} // namespace TwilliEngine