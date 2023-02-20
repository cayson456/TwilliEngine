#include "D3DBuffer.hpp"
namespace TwilliEngine
{

template <typename T>
bool D3DBuffer::Build()
{
    if (mIsBuilt) {
        err::LogError("Attempted to build already built buffer ", mName);
        return false;
    }

    if (!std::is_base_of<Buffer, T>()) {
        err::LogError("Attempted to build a buffer of type ", typeid(T).name(),
                      " but it is not a base of ", typeid(Buffer).name());

        return false;
    }

    D3D11_BUFFER_DESC desc;
    {
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.ByteWidth = sizeof(T);
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.Usage = D3D11_USAGE_DYNAMIC;

        HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, nullptr, &mBuffer);

        if (!err::HRCheck(hr)) {
            err::LogError("Unable to Create D3D Buffer: ", mName);
            return false;
        }
    }

    mBuilt = true;
    mByteWidth = sizeof(T);
    mBuffer = std::make_unique<T>();

    return true;
}

template<typename T>
inline T* D3DBuffer::GetBuffer()
{
    return nullptr;
}

template <typename T>
void D3DBuffer::MapDataToBuffer(const T& data)
{
    if (typeid(T) != typeid(*mBuffer.get())) {
        err::LogError("Attempted to map ");
    }


    if (!mIsBuilt) {
        err::LogError("Attempted to Map Unbuilt D3D Buffer");
        return;
    }

    D3D11_MAPPED_SUBRESOURCE mapped_buffer;
    HRESULT hr = D3D::GetInstance()->GetContext()->Map(mD3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

    if (!err::HRCheck(hr)) {
        err::LogError("Unable to Map D3D Buffer");
        return;
    }

    std::memcpy(mapped_buffer.pData, data, mByteWidth);
    D3D::GetInstance()->GetContext()->Unmap(mBuffer, 0);
}
} // namespace TwilliEngine