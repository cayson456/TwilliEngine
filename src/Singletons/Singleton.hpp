#pragma once
#include <memory>

namespace TwilliEngine
{

template <typename T>
class Singleton
{
public:
    Singleton() = default;
    ~Singleton() = default;
  
    template <typename ...Args>
    static void Initialize(Args &&... args);

    static void Shutdown();
    static T* GetInstance();

private:
    static std::unique_ptr<T> sInstance;
};

}

#include "Singleton.inl"