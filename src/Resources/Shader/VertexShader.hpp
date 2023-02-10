#pragma once
#include "Resources/Shader/Shader.hpp"

#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{

class VertexShader : public Shader
{
public:
    VertexShader(D3D* d3d, const std::filesystem::path &filepath);
    ~VertexShader();

    void LoadShader(const std::wstring &filepath) override;
    void Bind() override;

   // static ResourceID Create();

private:
    void CreateInputLayout(const std::string &filename, ID3DBlob *vertex_shader);

    ID3D11InputLayout* mInputLayout;
    ID3D11VertexShader *mVertexShader;  

};

} // namespace TwilliEngine