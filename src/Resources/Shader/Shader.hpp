#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"

namespace TwilliEngine
{
class Shader : public ResourceBase<Shader>
{
public:
    Shader();
    ~Shader();

    virtual void Bind() = 0;

    enum Type
    {
        Vertex,
        Pixel,
        Compute,
        COUNT
    };

private:
    std::map<size_t, D3DBuffer::Key> mAssignedBuffers;
};



} // namespace TwilliEngine