#pragma once

#include "WinWrap.h"
#include <d3d11.h>
#include <wrl.h>

class Color;



class Graphics
{
	public:

		struct Vertex {
			float x;
			float y;
		};

	public:

		Graphics() = default;
		~Graphics();

		void Initialize(HWND hWnd);
		void BeginFrame();
		void EndFrame();
		void DrawTriangleTest();
		void ClearBuffer(float red, float green, float blue);
		void PutPixel(int x, int y, Color c);
		void PutPixel(int x, int y, int r, int g, int b);
		void DrawRectangle(int x, int y, int width, int height, const Color& c);
		void DrawCircle(int x, int y, int radius, Color c);

	public:

		static const int ScreenWidth = 800; // TODO: use these or window's ones?
		static const int ScreenHeight = 800;

	private:

		struct FSQVertex // full-screen textured quad, vertex format
		{
			float x, y, z;		// position
			float u, v;			// texture coordinates
		};

	private:

		Microsoft::WRL::ComPtr <ID3D11Device> mDevice = nullptr;                           // device:             used for creating and managing DirectX resources
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> mDeviceContext = nullptr;             // device context:     used to send commands to GPU 
		Microsoft::WRL::ComPtr <IDXGISwapChain> mSwapChain = nullptr;                      // swap chain:         collection of buffers, used for displaying images on screen
		Microsoft::WRL::ComPtr <ID3D11RenderTargetView> mRenderTargetView = nullptr;       // render target view: used to specify which part of the swap chain should be used for rendering
		Microsoft::WRL::ComPtr <ID3D11Texture2D> mSysBufferTexture = nullptr;              // buffer texture:     2D texture, used to store the contents of the frame buffer
		Microsoft::WRL::ComPtr <ID3D11ShaderResourceView> mSysBufferTextureView = nullptr; // shader res. view:   used to access contents of the frame buffer texture from shaders
		Microsoft::WRL::ComPtr <ID3D11PixelShader> mPixelShader = nullptr;                 // pixel shader:       used to render contents of the frame buffer
		Microsoft::WRL::ComPtr <ID3D11VertexShader> mVertexShader = nullptr;               // vertex shader:      used to render contents of the frame buffer
		Microsoft::WRL::ComPtr <ID3D11Buffer> mVertexBuffer = nullptr;                     // vertex buffer:      used to specify the positions of the vertices that make up the full-screen quad
		Microsoft::WRL::ComPtr <ID3D11InputLayout> mInputLayout = nullptr;                 // input layout:       used to specify the input data format for the vertex shader
		Microsoft::WRL::ComPtr <ID3D11SamplerState> mSamplerState = nullptr;               // sampler state:      used to specify how the frame buffer texture should be sampled when used in shaders

		Color* mSysBuffer = nullptr;

		D3D11_MAPPED_SUBRESOURCE  mappedSysBufferTexture;                        // mapped subresource: used to map the frame buffer texture to system memory so it can be modified
};

