#include "Graphics.h"

#include "WinWrap.h"
#include <d3d11.h>
#include <wrl.h>

#include "Color.h"
#include <assert.h>
#include "Window.h"

#include <iostream>
#include <string>
#include <stdio.h>

#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using Microsoft::WRL::ComPtr;

void Graphics::Initialize(HWND hWnd)
{
	assert(hWnd != nullptr);

	// Create Device and Swap Chain

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc)); // ?
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = Graphics::ScreenWidth;
	swapChainDesc.BufferDesc.Height = Graphics::ScreenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 1u;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 60u;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1u;
	swapChainDesc.SampleDesc.Quality = 0u;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0u;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,                        // Adapter (use default)
		D3D_DRIVER_TYPE_HARDWARE,       // Driver type (use hardware)
		nullptr,                        // Software rasterizer module
		D3D11_CREATE_DEVICE_DEBUG,      // Debug flag
		nullptr,                        // Feature levels
		0,                              // Number of feature levels
		D3D11_SDK_VERSION,              // SDK version
		&swapChainDesc,                 // Swap chain description
		&mSwapChain,                    // Swap chain pointer
		&mDevice,                       // Device pointer
		nullptr,                        // Feature level
		&mDeviceContext                 // Device context pointer
	);
	assert(SUCCEEDED(hr));

	// Gain access to texture subresource (back buffer) in swap chain

	ComPtr<ID3D11Resource> mBackBuffer;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mBackBuffer);
	assert(SUCCEEDED(hr));

	// Create view on BackBuffer that we can render to

	hr = mDevice->CreateRenderTargetView(mBackBuffer.Get(), nullptr, &mRenderTargetView);
	assert(SUCCEEDED(hr));

	// Set back-buffer as the render target using created view

	mDeviceContext->OMSetRenderTargets(1u, mRenderTargetView.GetAddressOf(), nullptr);

	// set viewport dimensions

	D3D11_VIEWPORT vp;
	vp.Width = float(Graphics::ScreenWidth);
	vp.Height = float(Graphics::ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &vp);

	// allocate memory for sysbuffer (16-byte aligned for faster access)

	mSysBuffer = reinterpret_cast<Color*>(
		_aligned_malloc(sizeof(Color) * Graphics::ScreenWidth * Graphics::ScreenHeight, 16u));

	// Create texture for cpu render target <---------- what's happening after this?

	//D3D11_TEXTURE2D_DESC sysTexDesc;
	//sysTexDesc.Width = Graphics::ScreenWidth;
	//sysTexDesc.Height = Graphics::ScreenHeight;
	//sysTexDesc.MipLevels = 1;
	//sysTexDesc.ArraySize = 1;
	//sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//sysTexDesc.SampleDesc.Count = 1;
	//sysTexDesc.SampleDesc.Quality = 0;
	//sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	//sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//sysTexDesc.MiscFlags = 0;

	//hr = mDevice->CreateTexture2D(&sysTexDesc, nullptr, &mSysBufferTexture);
	//assert(SUCCEEDED(hr));

	//// Create the resource view on the texture

	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//srvDesc.Format = sysTexDesc.Format;
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = 1;

	//hr = mDevice->CreateShaderResourceView(mSysBufferTexture.Get(), &srvDesc, &mSysBufferTextureView);
	//assert(SUCCEEDED(hr));

}

Graphics::~Graphics()
{
	// Free sysbuffer memory (aligned free)

	if (mSysBuffer)
	{
		_aligned_free(mSysBuffer);
		mSysBuffer = nullptr;
	}

	// Clear the state of the device context before destruction

	if (mDeviceContext) mDeviceContext->ClearState();
}

void Graphics::ClearBuffer(float red, float green, float blue)
{
	const float colorArr[] = { red,green,blue,1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), colorArr);
}

void Graphics::BeginFrame()
{
	// Clear the sysbuffer

	memset(mSysBuffer, 0u, sizeof(Color) * Graphics::ScreenHeight * Graphics::ScreenWidth);
}

void Graphics::EndFrame()
{
	// flip back/front buffers

	HRESULT hr = mSwapChain->Present(1u, 0u);
	assert(SUCCEEDED(hr));
}

void Graphics::PutPixel(int x, int y, Color c)
{
	// check pixel within screen
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));

	mSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::PutPixel(int x, int y, int r, int g, int b)
{
	PutPixel(x, y, Color(unsigned char(r), unsigned char(g), unsigned char(b)));
}

void Graphics::DrawRectangle(int x, int y, int width, int height, const Color& c)
{
	for (int iy = y; iy < height; ++iy)
	{
		for (int ix = x; ix < width; ++ix)
		{
			PutPixel(ix, iy, c);
		}
	}
}

void Graphics::DrawCircle(int x, int y, int radius, Color c)
{
	const int rad_sq = radius * radius;
	for (int y_loop = y - radius + 1; y_loop < y + radius; y_loop++)
	{
		for (int x_loop = x - radius + 1; x_loop < x + radius; x_loop++)
		{
			const int x_diff = x - x_loop;
			const int y_diff = y - y_loop;
			if (x_diff * x_diff + y_diff * y_diff <= rad_sq)
			{
				PutPixel(x_loop, y_loop, c);
			}
		}
	}
}


/////////////

void Graphics::DrawTriangleTest()
{
	const Vertex triangleVerts[] =
	{
		{ 0.0f,  0.5f},
		{ 0.5f, -0.5f},
		{-0.5f, -0.5f},
	};

	// Create vertex buffer: a centered 2D triangle

	//ComPtr<ID3D11Buffer> pVertexBuffer;

	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(triangleVerts);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = triangleVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &sd, &mVertexBuffer); // TODO: use mVertexBuffer instead
	assert(SUCCEEDED(hr));

	// Bind vertex buffer to pipeline

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	mDeviceContext->IASetVertexBuffers(0u, 1u, mVertexBuffer.GetAddressOf(), &stride, &offset);

	// Create pixel shader

	//ComPtr<ID3D11PixelShader> pPixelShader;
	ComPtr<ID3DBlob> pBlob;
	hr = D3DReadFileToBlob(L"PixelShaderOne.cso", &pBlob);
	assert(SUCCEEDED(hr));
	hr = mDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &mPixelShader);
	assert(SUCCEEDED(hr));
	mDeviceContext->PSSetShader(mPixelShader.Get(), nullptr, 0u); // binds pixel shader to pipeline

	// Create vertex shader

	//ComPtr<ID3D11VertexShader> pVertexShader;
	hr = D3DReadFileToBlob(L"VertexShaderOne.cso", &pBlob);
	assert(SUCCEEDED(hr));
	hr = mDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &mVertexShader);
	assert(SUCCEEDED(hr));
	mDeviceContext->VSSetShader(mVertexShader.Get(), nullptr, 0u); // binds vertex shader to pipeline

	// Input (vertex) layout (2D position only)

	//ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		// array of descriptors, describes our vertex format
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = mDevice->CreateInputLayout(
		ied,
		(UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&mInputLayout);
	assert(SUCCEEDED(hr));

	// Bind vertex layout

	mDeviceContext->IASetInputLayout(mInputLayout.Get());

	// Bind render target

	mDeviceContext->OMSetRenderTargets(1u, mRenderTargetView.GetAddressOf(), nullptr);

	// Set primitive topology to triangle list (groups of 3 vertices)

	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Viewport

	D3D11_VIEWPORT viewport;
	viewport.Width = float(Graphics::ScreenWidth);
	viewport.Height = float(Graphics::ScreenHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1u, &viewport);

	// Draw

	UINT vertexCount = (UINT)std::size(triangleVerts);
	mDeviceContext->Draw(vertexCount, 0u);
}
