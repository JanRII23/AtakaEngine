#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <Windows.h>
#include <DX3D/Core/InputListener.h>

namespace dx3d
{
	class GraphicsEngine final: public Base, public InputListener
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;
		void render(SwapChain& swapChain);
		void updateTime();
		//NOTE: Inherited via InputListener
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
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
		ULONGLONG m_old_delta = 0;
		ULONGLONG m_new_delta = 0;
		f32 m_delta_time = 0.0f;
		f32 m_delta_pos = 0.0f;
		f32 m_delta_scale = 0.0f;

		f32 m_rot_x = 0.0f;
		f32 m_rot_y = 0.0f;
	};
}


