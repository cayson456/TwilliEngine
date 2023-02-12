#pragma once
#include "Resources/Shader/Shader.hpp"

#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{

class VertexShader : public Shader
{
public:
    VertexShader() : mInputLayout(nullptr), mVertexShader(nullptr) {}
    VertexShader(const std::string& name) : Shader(name), mInputLayout(nullptr), mVertexShader(nullptr) {}
    ~VertexShader();

    void Build(const std::filesystem::path& filepath) override;
    void Bind() override;

   // static ResourceID Create();

private:
        // NOTE:
        // Create input layout per vertex shader cause it seems easier that way...
        // It's not like it's resource intensive to rebind duplicate ones anyway i think
    void CreateInputLayout(const std::string &filename, ID3DBlob *vertex_shader);

    ID3D11InputLayout* mInputLayout;
    ID3D11VertexShader *mVertexShader;  
};

} // namespace TwilliEngine