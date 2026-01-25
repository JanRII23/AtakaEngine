#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d
{
	struct RenderResourceDesc
	{
		BaseDesc base;
		std::shared_ptr<const RenderSystem> renderDevice;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};

	class RenderResource : public Base
	{
	public:
		explicit RenderResource(const RenderResourceDesc& desc) :
			Base(desc.base),
			m_renderDevice(desc.renderDevice),
			m_device(desc.device),
			m_factory(desc.factory)
		{

		}

	protected:
		std::shared_ptr<const RenderSystem> m_renderDevice;
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;
	};
}
