#pragma once
#include "Systems/System.hpp"
#include <direct.h>

namespace TwilliEngine
{
class WorldSystem : public System
{
public:
    WorldSystem();
    ~WorldSystem() noexcept;

    void StartFrame();
    void Update(float dt);
    void EndFrame();

private:
    
    
    LRESULT ProcessMessage(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam);

        // Register Window Classes in Input System because it needs the 
    void RegisterWindowClasses();
    void UnregisterWindowClasses();
};

} // namespace TwilliEngine