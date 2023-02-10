#pragma once
#include "Resources/Shader/Shader.hpp"

namespace TwilliEngine
{

class ComputeShader : public Shader
{
public:
    ComputeShader();
    ~ComputeShader();

    void LoadShader(const std::wstring &filepath) override;
    void Bind() override;

//    static ResourceID Create();

private:
    ID3D11ComputeShader *mComputeShader;

};

} // namespace TwilliEngine