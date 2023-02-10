#include "precompiled.hpp"
#include "Core/Core.hpp"

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);


    TwilliEngine::Core core;
    core.Run();
    core.Shutdown();

    return 0;
}