#pragma once
#include <DX3D/Math/Point.h>
#include <DX3D/Math/Rect.h>

namespace dx3d
{
	class InputListener
	{
	public:
		InputListener()
		{
		}
		~InputListener()
		{
		}

		//NOTE: Keyboard pure virtual callback functions
		virtual void onKeyDown(int key) = 0;
		virtual void onKeyUp(int key) = 0;

		//NOTE: Mouse pure virtual callback functions
		virtual void onMouseMove(const Point& mouse_pos, const Rect& size) = 0;

		virtual void onLeftMouseDown(const Point& mouse_pos) = 0;
		virtual void onLeftMouseUp(const Point& mouse_pos) = 0;

		virtual void onRightMouseDown(const Point& mouse_pos) = 0;
		virtual void onRightMouseUp(const Point& mouse_pos) = 0;

		InputListener* getInputListener() const
		{
			return m_listener;
		}

	private:
		InputListener* m_listener{};
	};
}