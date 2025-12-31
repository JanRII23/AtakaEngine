#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
	class GraphicsEngine final: public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;
		void render(SwapChain& swapChain);
		void updateTime();
	private:
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
			Vec4 color1;
		};
	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};
		ConstantBufferPtr m_cb{};
		IndexBufferPtr m_ib{};
	private:
		f32 m_old_delta;
		f32 m_new_delta;
		f32 m_delta_time;
		f32 m_delta_pos;
		f32 m_delta_scale;
	};
}


