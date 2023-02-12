#pragma once
#include "Resources/Shader/Shader.hpp"

namespace TwilliEngine
{

class PixelShader : public Shader
{
public:
    PixelShader() : mPixelShader(nullptr) {}
    PixelShader(const std::string& name) : Shader(name), mPixelShader(nullptr) {}
    ~PixelShader();

    void Build(const std::filesystem::path& filepath) override;
    void Bind() override;

  //  static ResourceID Create();

private:
    ID3D11PixelShader *mPixelShader;

};

} // namespace TwilliEngine