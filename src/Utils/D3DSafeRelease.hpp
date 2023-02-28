#pragma once

template <typename T>
static inline void SafeRelease(T* &rhs)
{
    if (rhs) rhs->Release();
    rhs = nullptr;
}