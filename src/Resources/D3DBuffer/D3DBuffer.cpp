#include "precompiled.hpp"
#include "D3DBuffer.hpp"

namespace TwilliEngine
{

D3DBuffer::~D3DBuffer()
{
    SafeRelease(mD3DBuffer);
}


} // namespace TwilliEngine