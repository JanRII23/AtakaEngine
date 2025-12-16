#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc): Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX3DGraphicsLogErrorAndThrow(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, 0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext), "Direct3D11 Initialization Failed.");

	DX3DGraphicsLogErrorAndThrow(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface Failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogErrorAndThrow(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent Failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogErrorAndThrow(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent Failed to retrieve IDXGIFactory.");
}

dx3d::RenderSystem::~RenderSystem()
{
}
