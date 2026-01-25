#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <d3dcompiler.h>

namespace dx3d
{
	//TODO: figure out the 15:45 VertexShader + PixelShader don't have these??
	class VertexShaderSignature final: public GraphicsResource
	{
	public:
		VertexShaderSignature(const VertexShaderSignatureDesc& desc, const GraphicsResourceDesc& gDesc);
		BinaryData getShaderBinaryData() const noexcept;
		BinaryData getInputElementsData() const noexcept;
	private:
		ShaderBinaryPtr m_vsBinary{};
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> m_shaderReflection{};
		D3D11_INPUT_ELEMENT_DESC m_elements[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{};
		ui32 m_numElements{};
		UINT currentOffset = 0;
	};
}



