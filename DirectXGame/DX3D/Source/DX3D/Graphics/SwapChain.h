#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class SwapChain final: public GraphicsResource
	{
	public:
		SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);
		Rect getSize() noexcept;
		void resize(unsigned int width, unsigned int height);
		void present(bool vsync = false);
		void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	private:
		void reloadBuffers(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv{};
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_dsv{};
		Rect m_size{};

		friend class DeviceContext;
	};
}
