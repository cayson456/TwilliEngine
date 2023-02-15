#include "precompiled.hpp"
#include "SwapChain.hpp"

#include "Singletons/Window/Window.hpp"

namespace TwilliEngine {

SwapChain::SwapChain() : mSwapChain(nullptr),
                         mRenderTargetView(nullptr),
                         mDepthStencilBuffer(nullptr),
                         mDepthStencilState(nullptr),
                         mDepthStencilView(nullptr),
                         mRasterizerState(nullptr),
                         mBlendState(nullptr)
                                                            
{

        // Initialize Everything
    CreateSwapChainBuffer(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    CreateRenderTargetView();
    CreateRasterizerState();
    CreateDepthStencilState();
    CreateDepthBuffer(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    CreateDepthStencilView();
    CreateBlendState();
    SetViewport(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    mIsInitialized = true;
}

SwapChain::~SwapChain()
{
    SafeRelease(mSwapChain);
    SafeRelease(mRenderTargetView);
    SafeRelease(mDepthStencilBuffer);
    SafeRelease(mDepthStencilState);
    SafeRelease(mRasterizerState);
    SafeRelease(mBlendState);
}

void SwapChain::BindSwapChain()
{
    D3D::GetInstance()->GetContext()->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
    D3D::GetInstance()->GetContext()->OMSetDepthStencilState(mDepthStencilState, 0xFF);
    D3D::GetInstance()->GetContext()->OMSetBlendState(mBlendState, nullptr, 0xFFFFFFFF);
}

void SwapChain::ClearSwapChain()
{
    const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    D3D::GetInstance()->GetContext()->ClearRenderTargetView(mRenderTargetView, clear_color);
    D3D::GetInstance()->GetContext()->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void SwapChain::Present()
{
    mSwapChain->Present(1, 0);
}

void SwapChain::ResizeBuffers(UINT width, UINT height)
{
    if (!mSwapChain)
        return;

    BindSwapChain();
    SafeRelease(mRenderTargetView);

    HRESULT hr = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    err::Assert(err::HRCheck(hr), " Unable to Resize SwapChain Buffer");
    
    CreateRenderTargetView();
    CreateDepthStencilView();

    BindSwapChain();
    SetViewport(width, height);
}

void SwapChain::CreateSwapChainBuffer(UINT width, UINT height)
{
    SafeRelease(mSwapChain);

        // Multisampling Parameters
    constexpr UINT SAMPLE_COUNT = 1;
    UINT num_quality_levels;
    D3D::GetInstance()->GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, SAMPLE_COUNT, &num_quality_levels);

    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));

        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 2;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    }

    IDXGIDevice* pDXGIDevice;
    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice)),
                "Unable to create Swap Chain Buffer");

    IDXGIAdapter* pDXGIAdapter;
    err::Assert(err::HRCheck(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDXGIAdapter)),
                "Unable to create Swap Chain Buffer");

    IDXGIFactory6* pIDXGIFactory;
    err::Assert(err::HRCheck(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIDXGIFactory)),
                "Unable to create Swap Chain Buffer");

    err::Assert(err::HRCheck(pIDXGIFactory->CreateSwapChainForHwnd(D3D::GetInstance()->GetDevice(), Window::GetInstance()->GetHandle(), &sd, NULL, NULL, &mSwapChain)),
                "Unable to create Swap Chain Buffer");
}
void SwapChain::CreateRenderTargetView()
{
    SafeRelease(mRenderTargetView);

    DXGI_SWAP_CHAIN_DESC sd;
    mSwapChain->GetDesc(&sd);

    ID3D11Texture2D* back_buffer_texture;
    D3D11_RENDER_TARGET_VIEW_DESC desc;

    err::Assert(err::HRCheck(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_texture)),
        "Failed to get the Swap Chain Back Buffer");

    desc.Format = sd.BufferDesc.Format;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateRenderTargetView(back_buffer_texture, &desc, &mRenderTargetView)),
        "Failed to create the Render Target View");

    SafeRelease(back_buffer_texture);
}
void SwapChain::CreateRasterizerState()
{
    SafeRelease(mRasterizerState);

    D3D11_RASTERIZER_DESC desc;

    desc.AntialiasedLineEnable = false;
    desc.CullMode = D3D11_CULL_BACK;
    desc.DepthBias = 0;
    desc.DepthBiasClamp = 0.0f;
    desc.DepthClipEnable = true;
    desc.FillMode = D3D11_FILL_SOLID;
    desc.FrontCounterClockwise = true; // RH Coordinate System
    desc.MultisampleEnable = false;
    desc.ScissorEnable = false;
    desc.SlopeScaledDepthBias = 0.0f;

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateRasterizerState(&desc, &mRasterizerState)),
        "Unable to Create Rasterizer State");

    D3D::GetInstance()->GetContext()->RSSetState(mRasterizerState);
}
void SwapChain::CreateDepthStencilState()
{
    SafeRelease(mDepthStencilState);

    D3D11_DEPTH_STENCIL_DESC desc;

    desc.DepthEnable = false;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS;

    desc.StencilEnable = true;
    desc.StencilReadMask = 0xFF;
    desc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing.
    desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing.
    desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateDepthStencilState(&desc, &mDepthStencilState)),
        "ERROR: Unable to Create Depth Stencil State");

    D3D::GetInstance()->GetContext()->OMSetDepthStencilState(mDepthStencilState, 1);
}
void SwapChain::CreateDepthBuffer(UINT width, UINT height)
{
    SafeRelease(mDepthStencilBuffer);

    D3D11_TEXTURE2D_DESC desc;

    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateTexture2D(&desc, NULL, &mDepthStencilBuffer)),
        "ERROR: Unable To Create Depth Stencil Buffer");
}
void SwapChain::CreateDepthStencilView()
{
    SafeRelease(mDepthStencilView);

    D3D11_DEPTH_STENCIL_VIEW_DESC desc;

    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    desc.Texture2D.MipSlice = 0;
    desc.Flags = 0;

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateDepthStencilView(mDepthStencilBuffer, &desc, &mDepthStencilView)),
        "ERROR: Unable To Create Depth Stencil View");
}
void SwapChain::CreateBlendState()
{
    SafeRelease(mBlendState);

    D3D11_BLEND_DESC desc;

    desc.AlphaToCoverageEnable = false;
    desc.IndependentBlendEnable = false;

    for (unsigned i = 0; i < 8; ++i) {
        desc.RenderTarget[i].BlendEnable = true;
        desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
        desc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
        desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
        desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[i].RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
    }

    err::Assert(err::HRCheck(D3D::GetInstance()->GetDevice()->CreateBlendState(&desc, &mBlendState)),
        "ERROR: Unable to Create Blend State");

    D3D::GetInstance()->GetContext()->OMSetBlendState(mBlendState, NULL, 0xFFFFFFFF);
}
void SwapChain::SetViewport(UINT width, UINT height)
{
    D3D11_VIEWPORT vp;
    vp.Width = static_cast<float>(width);
    vp.Height = static_cast<float>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 1.0f;

    D3D::GetInstance()->GetContext()->RSSetViewports(1, &vp);
}
}