#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d
{
	class GraphicsDevice final: public Base, public std::enable_shared_from_this<GraphicsDevice>
	{
	public:
		explicit GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() override;

		SwapChainPtr createSwapChain(const SwapChainDesc& desc);
		DeviceContextPtr createDeviceContext();
		ShaderBinaryPtr compileShader(const ShaderCompileDesc& desc);
		GraphicsPipelineStatePtr createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc);
		VertexBufferPtr createVertexBuffer(const VertexBufferDesc& desc);
		VertexShaderSignaturePtr createVertexShaderSignature(const VertexShaderSignatureDesc& desc);
		ConstantBufferPtr createConstantBuffer(const ConstantBufferDesc& desc);
		IndexBufferPtr createIndexBuffer(const IndexBufferDesc& desc);
		TextureBufferPtr createTextureBufferPtr(const TextureBufferDesc& desc);
		ID3D11Device* getD3DDevice() const noexcept;
		void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

		void executeCommandList(DeviceContext& context);
	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;
		void** m_mesh_layout_byte_code;
		size_t m_mesh_layout_size;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}


