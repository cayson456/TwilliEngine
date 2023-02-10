#pragma once
#include <d3d11.h>

namespace TwilliEngine
{
class SwapChain
{
public:
    SwapChain(HWND window);
    ~SwapChain();

    void BindSwapChain();
    void ClearSwapChain();

    void ResizeBuffers(UINT width, UINT height, HWND window);
private:

    void CreateSwapChainBuffer(UINT width, UINT height, HWND window);
    

    void CreateRenderTargetView();
    void CreateRasterizerState();
    void CreateDepthStencilState();
    void CreateDepthBuffer(UINT width, UINT height);
    void CreateDepthStencilView();
    void CreateBlendState();
    void SetViewport(UINT width, UINT height);

public:
    IDXGISwapChain1* mSwapChain;
    ID3D11RenderTargetView* mRenderTargetView;
    ID3D11Texture2D* mDepthStencilBuffer;
    ID3D11DepthStencilState* mDepthStencilState;
    ID3D11DepthStencilView* mDepthStencilView;
    ID3D11RasterizerState* mRasterizerState;
    ID3D11BlendState* mBlendState;
};

} // namespace TwilliEngine