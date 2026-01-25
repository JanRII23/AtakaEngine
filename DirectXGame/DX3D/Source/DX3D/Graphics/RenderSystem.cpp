#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>

using namespace dx3d;

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc) : Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX3DGraphicsLogThrowOnFail(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, 0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext), "Direct3D11 Initialization Failed.");

	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface Failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent Failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent Failed to retrieve IDXGIFactory.");
}

dx3d::RenderSystem::~RenderSystem()
{
}

SwapChainPtr dx3d::RenderSystem::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc, getRenderSystemDesc());
}

DeviceContextPtr dx3d::RenderSystem::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getRenderSystemDesc());
}

ShaderBinaryPtr dx3d::RenderSystem::compileShader(const ShaderCompileDesc& desc)
{
	return std::make_shared<ShaderBinary>(desc, getRenderSystemDesc());
}

GraphicsPipelineStatePtr dx3d::RenderSystem::createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc)
{
	return std::make_shared<GraphicsPipelineState>(desc, getRenderSystemDesc());
}

VertexBufferPtr dx3d::RenderSystem::createVertexBuffer(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexBuffer>(desc, getRenderSystemDesc());
}

VertexShaderSignaturePtr dx3d::RenderSystem::createVertexShaderSignature(const VertexShaderSignatureDesc& desc)
{
	return std::make_shared<VertexShaderSignature>(desc, getRenderSystemDesc());
}

ConstantBufferPtr dx3d::RenderSystem::createConstantBuffer(const ConstantBufferDesc& desc)
{
	return std::make_shared<ConstantBuffer>(desc, getRenderSystemDesc());
}

IndexBufferPtr dx3d::RenderSystem::createIndexBuffer(const IndexBufferDesc& desc)
{
	//TODO: update these tho
	return std::make_shared<IndexBuffer>(desc, getRenderSystemDesc());
}

void dx3d::RenderSystem::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList Failed.");
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

RenderResourceDesc dx3d::RenderSystem::getRenderSystemDesc() const noexcept
{
	return { {m_logger}, shared_from_this() , *m_d3dDevice.Get(), *m_dxgiFactory.Get() };
}
