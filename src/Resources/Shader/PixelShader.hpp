#pragma once
#include "Resources/Shader/Shader.hpp"

namespace TwilliEngine
{

class PixelShader : public Shader, public ResourceBase<PixelShader>
{
public:
    PixelShader() : mPixelShader(nullptr) {}
    PixelShader(const std::string& name) : ResourceBase(name), mPixelShader(nullptr) {}
    ~PixelShader();

    bool Build(const std::filesystem::path& filepath) override;
    void Bind() override;

  //  static ResourceID Create();

private:
    ID3D11PixelShader *mPixelShader;

};

} // namespace TwilliEngine