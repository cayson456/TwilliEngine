#include "precompiled.hpp"
#include "Model.hpp"


namespace TwilliEngine
{
Model::~Model()
{
    for (auto mesh : mMeshes) {
        mesh.Destroy();
    }
}

void Model::Build()
{
    for (auto mesh_key : mMeshes) {
        if (!mesh_key->IsBuilt()) {
            err::LogError("Attempted to Build a model with an unbuilt mesh! ", mName);
            return;
        }
    }

    mIsBuilt = true;
}

void Model::Draw()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to draw unbuilt model! ", mName);
        return;
    }

    for (auto &mesh : mMeshes) {
        mesh->Bind();

        D3D::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3D::GetInstance()->GetContext()->DrawIndexed(mesh->mNumIndices, 0, 0);
    }
}
}