#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"

namespace TwilliEngine
{
class Model : public ResourceBase<Model>
{
public:
    Model() : mHasSkeleton(false) {}
    Model(std::string_view name) : ResourceBase(name), mHasSkeleton(false) {}
    ~Model();

    void Build();

    void Draw();
    void AppendMesh(Mesh::Key mesh) { mMeshes.push_back(mesh); };

    bool mHasSkeleton;

private:
    std::vector<Mesh::Key> mMeshes;
};



} // namespace TwilliEngine