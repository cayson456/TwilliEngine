#pragma once
#include "Singletons/Singleton.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"
#include "Resources/StructuredBuffer/StructuredBuffer.hpp"

namespace TwilliEngine
{
class ResourceLoader
{
public:
    ResourceLoader() {}
    ~ResourceLoader() {}

    void LoadAllAssetsInFolder();
    void UnloadAllAssets();

    Model::Key LoadModel(const std::filesystem::path &path);
    ShaderProgram::Key LoadShaderProgram(const std::filesystem::path &path);
    D3DBuffer::Key LoadConstantBuffer(const std::filesystem::path& path);
    StructuredBuffer::Key LoadStructuredBuffer(const std::filesystem::path& path);

private:
    void LoadAllModels();
    void LoadAllShaderPrograms();
    void LoadAllConstantBuffers();
    void LoadAllStructuredBuffers();
};


}