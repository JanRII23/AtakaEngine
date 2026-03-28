#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Vector2D.h>
#include <Windows.h>
#include <DX3D/Core/InputListener.h>
#include <DX3D/Core/IFocusListener.h>
#include <DX3D/Math/Matrix4x4.h>
#include <DX3D/Graphics/ResourceManager/TextureManager/TextureManager.h>

namespace dx3d
{
	class GraphicsEngine final: public Base, public InputListener, public IFocusListener
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;
		void render(SwapChain& swapChain);
		void updateTime();
		void updateTargetPosition();
		void onFocus() override;
		void onKillFocus() override;

		//NOTE: Inherited via InputListener
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
		void onMouseMove(const Point& mouse_pos, const Rect& size) override;

		void onLeftMouseDown(const Point& mouse_pos) override;
		void onLeftMouseUp(const Point& mouse_pos) override;

		void onRightMouseDown(const Point& mouse_pos) override;
		void onRightMouseUp(const Point& mouse_pos) override;

		TextureManager* getTextureManager() noexcept;

	private:
		struct Vertex
		{
			Vec3 position;
			Vector2D texcoord;
			/*Vec4 color;
			Vec4 color1;*/
		};
	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};
		ConstantBufferPtr m_cb{};
		IndexBufferPtr m_ib{};
		TextureManager * m_tex_manager = nullptr;
		TextureBufferPtr m_tex{};
		TexturePtr m_wood_tex;


	private:
		ULONGLONG m_old_delta = 0;
		ULONGLONG m_new_delta = 0;
		f32 m_delta_time = 0.0f;
		f32 m_delta_pos = 0.0f;
		f32 m_delta_scale = 0.0f;

		f32 m_rot_x = 0.0f;
		f32 m_rot_y = 0.0f;

		f32 m_scale_cube = 1;
		f32 m_forward = 0.0f;
		f32 m_current_forward = 0.0f;
		f32 m_rightward = 0.0f;
		f32 m_current_rightward = 0.0f;

		Matrix4x4 m_world_cam;
	};
}


