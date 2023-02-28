#pragma once
#include "Systems/System.hpp"

namespace TwilliEngine
{
class Core
{
public:
    Core() = default;
    ~Core() = default;
  
    void Run();
    void Shutdown();
 
    template <typename T>
    T* GetSystem() const;

private:

    template <typename T>
    void StartSystem();

    static bool bRunning;

    std::vector<std::unique_ptr<System>> mSystems;
};


template <typename T>
inline void Core::StartSystem()
{
    static_assert(std::is_base_of<System, T>::value, 
                "Attempted add something other than a system into Core");

    mSystems.push_back(std::move(std::make_unique<T>()));
    mSystems.back()->Enable();
}

template <typename T>
inline T* Core::GetSystem() const
{
    for (auto& sys : mSystems) {
        if (std::is_class<T>(sys.get()))
            return sys.get();
    }

    return nullptr;
}

} // namespace TwilliEngine