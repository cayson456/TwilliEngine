#pragma once
#include "Singletons/Singleton.hpp"

namespace TwilliEngine {
class Window : public Singleton<Window>
{
public:
    Window(UINT screen_width = GetSystemMetrics(SM_CXSCREEN),
           UINT screen_height = GetSystemMetrics(SM_CYSCREEN),
           UINT resolution_width = GetSystemMetrics(SM_CXSCREEN),
           UINT resolution_height = GetSystemMetrics(SM_CYSCREEN),
           const std::string& window_name = {"Twilli Engine"});
    ~Window();

    static LRESULT ProcessMessage(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam);

    HWND GetHandle() const { return mWindowHandle; }

private:
    HWND mWindowHandle;
    
    std::pair<UINT, UINT> mScreenSize;
    std::pair<UINT, UINT> mResolution;
};

} // namespace TwilliEngine