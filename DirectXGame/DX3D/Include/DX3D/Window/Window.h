#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/IFocusListener.h>

namespace dx3d
{
	class Window: public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

		void setHWND(HWND hwnd);
		void setFocusListener(IFocusListener* listener);
		void onFocus();
		void onKillFocus();

	protected:
		void* m_handle{};
		Rect m_size{};
		HWND m_hwnd{};
		IFocusListener* m_focusListener{};
	};
}



