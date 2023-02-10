#pragma once
#include <d3d11.h>

namespace TwilliEngine
{
class SwapChain
{
public:
    SwapChain(HWND window, ID3D11Device* device, ID3D11DeviceContext* device_context);
    ~SwapChain();

    void BindSwapChain(ID3D11DeviceContext* context);
    void ClearSwapChain(ID3D11DeviceContext* context);

    void ResizeBuffers(ID3D11Device* device, ID3D11DeviceContext* context,
                       UINT width, UINT height, HWND window);
private:

    void CreateSwapChainBuffer(ID3D11Device* device, 
                               UINT width, UINT height, HWND window);
    

    void CreateRenderTargetView(ID3D11Device *device);
    void CreateRasterizerState(ID3D11Device *device, ID3D11DeviceContext *context);
    void CreateDepthStencilState(ID3D11Device* device, ID3D11DeviceContext* context);
    void CreateDepthBuffer(ID3D11Device* device, UINT width, UINT height);
    void CreateDepthStencilView(ID3D11Device* device);
    void CreateBlendState(ID3D11Device* device, ID3D11DeviceContext* context);
    void SetViewport(ID3D11DeviceContext* context, UINT width, UINT height);

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