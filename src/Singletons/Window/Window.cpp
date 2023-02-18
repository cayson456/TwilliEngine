#include "precompiled.hpp"
#include "DirectXTK/Keyboard.h"
#include "DirectXTK/Mouse.h"

#include "Window.hpp"
#include "Singletons/SwapChain/SwapChain.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace TwilliEngine 
{

Window::Window(UINT screen_width, UINT screen_height,
               UINT resolution_width, UINT resolution_height,
               const std::string& window_name) : mWindowHandle(NULL),
                                                 mScreenSize({screen_width, screen_height}),
                                                 mResolution({resolution_width, resolution_height})                                        
{
        // Main Window Class
    WNDCLASSEX wc;
    {
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = reinterpret_cast<WNDPROC>(&ProcessMessage);
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hIconSm = wc.hIcon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "MainWindowClass";
        wc.cbSize = sizeof(WNDCLASSEX);
    }

    ATOM class_name = RegisterClassEx(&wc);
    err::Assert(class_name, "Unable to Register Window Class");

        // Create Window
    int posX = (GetSystemMetrics(SM_CXSCREEN) - mScreenSize.first) / 2;
    int posY = (GetSystemMetrics(SM_CYSCREEN) - mScreenSize.second) / 2;

    mWindowHandle = CreateWindowA("MainWindowClass", window_name.c_str(),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, posX, posY, mScreenSize.first, mScreenSize.second,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    err::Assert(mWindowHandle, "Unable to Create Window");

    ShowWindow(mWindowHandle, SW_SHOW);
    UpdateWindow(mWindowHandle);

    mIsInitialized = true;
}

Window::~Window()
{
    if (!DestroyWindow(mWindowHandle))
        err::PrintLastWindowsError();
}

LRESULT Window::ProcessMessage(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, WParam, LParam))
        return true;

    switch (msg) {
    case WM_ACTIVATEAPP:
        DirectX::Keyboard::ProcessMessage(msg, WParam, LParam);
        DirectX::Mouse::ProcessMessage(msg, WParam, LParam);
        break;

    case WM_DESTROY:
    case WM_QUIT:
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        DirectX::Keyboard::ProcessMessage(msg, WParam, LParam);
        break;

    case WM_INPUT:
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEHOVER:
        DirectX::Mouse::ProcessMessage(msg, WParam, LParam);
        break;

    case WM_SIZE:
    {
        UINT width = LOWORD(LParam);
        UINT height = HIWORD(LParam);

        if (SwapChain::IsInitialized())
            SwapChain::GetInstance()->ResizeBuffers(width, height);
        break;
    }
    default:
        break;
    }

    return DefWindowProc(hwnd, msg, WParam, LParam);
}
} // namespace TwilliEngine