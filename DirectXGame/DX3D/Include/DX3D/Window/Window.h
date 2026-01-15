#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/IFocusListener.h>
#include <memory>

namespace dx3d
{
	class Window: public Base, public IFocusListener
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

		void setHWND(HWND hwnd);
		void setGraphicsEngine(GraphicsEngine* engine);

		void onFocus() override;
		void onKillFocus() override;

	protected:
		void* m_handle{};
		Rect m_size{};
		HWND m_hwnd{};
		GraphicsEngine* m_graphicsEngine = nullptr;
	};
}



