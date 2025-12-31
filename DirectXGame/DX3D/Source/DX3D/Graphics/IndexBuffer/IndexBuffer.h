#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class IndexBuffer final: public GraphicsResource
	{
	public:
		IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc);
		ui32 getSizeIndexList() const noexcept;
	private:
		ui32 m_size_list{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};

		friend class DeviceContext;
	};
}

