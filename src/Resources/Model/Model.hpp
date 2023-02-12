#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{
class Model : public ResourceBase<Model>
{
public:
    Model() {}
    Model(const std::string &name) : ResourceBase(name) {}
    ~Model() {}

    void Build();

    void Draw();
    void AppendMesh(Mesh::Key mesh) { mMeshes.push_back(mesh); };

private:
    std::vector<Mesh::Key> mMeshes;
};



} // namespace TwilliEngine