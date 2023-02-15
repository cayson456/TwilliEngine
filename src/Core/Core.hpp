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

    static void SetQuitFlag() { bRunning = false; }

private:

    template <typename T>
    inline void StartSystem();

    template <typename T>
    inline T* GetSystem() const;

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