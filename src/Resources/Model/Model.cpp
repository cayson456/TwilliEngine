#include "precompiled.hpp"
#include "Model.hpp"


namespace TwilliEngine
{
  Model::Model() {}
  Model::~Model() {}

  void Model::Draw()
  {
    for (auto &mesh : mMeshes) {
      mesh->Bind();

      D3D::GetInstance()->mDeviceContext->DrawIndexed(mesh->mNumIndices, 0, 0);
    }
  }
}