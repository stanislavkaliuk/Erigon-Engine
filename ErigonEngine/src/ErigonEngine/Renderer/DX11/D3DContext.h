#pragma once

#include "ErigonEngine/Renderer/GraphicsContext.h"
#include <d3d11.h>

namespace ErigonEngine
{
	class D3DContext : public GraphicsContext
	{
	public:

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

		D3DContext(HWND window);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		HWND* m_WindowHandle;
	};
}
