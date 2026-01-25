#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Graphics/RenderSystem.h>

namespace dx3d
{
	class ConstantBuffer final : public GraphicsResource
	{
	public:
		ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc, RenderSystem* system);
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		RenderSystem* m_system = nullptr;

		friend class DeviceContext;
	};
}