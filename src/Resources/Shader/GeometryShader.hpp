#pragma once
#include "Resources/Shader/Shader.hpp"

#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{

class GeometryShader : public Shader, public ResourceBase<GeometryShader>
{
public:
    GeometryShader() : mGeometryShader(nullptr) {}
    GeometryShader(std::string_view name) : ResourceBase(name), mGeometryShader(nullptr) {}
    ~GeometryShader();

    bool Build(const std::filesystem::path& filepath) override;
    void Bind() override;

private:
    ID3D11GeometryShader* mGeometryShader;
};

} // namespace TwilliEngine