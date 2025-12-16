#include <DX3D/Graphics/SwapChain.h>

dx3d::SwapChain::SwapChain(const GraphicsResourceDesc& desc): GraphicsResource(desc)
{
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	m_factory.CreateSwapChain(&m_device, );
}
