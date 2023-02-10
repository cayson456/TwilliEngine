#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{
class Model : public ResourceBase<Model>
{
public:
    Model();
    ~Model();

    bool Build();
    void Bind(D3D* d3d);

    void Draw();
    void AppendMesh(Mesh::Key mesh) { mMeshes.push_back(mesh); };

private:
    std::vector<Mesh::Key> mMeshes;
};



} // namespace TwilliEngine