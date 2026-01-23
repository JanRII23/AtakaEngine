#pragma once
#include <DX3D/Core/InputListener.h>
#include <DX3D/Core/Common.h>
#include <map>
#include <DX3D/Math/Point.h>
#include <unordered_set>

namespace dx3d
{
	class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();

		void update(const Rect& size);
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);
		void setCursorPosition(const Point& pos);
		void showCursor(bool showMouse);

		static InputSystem* get();
	private:
		std::unordered_set<InputListener*> m_set_listeners;
		uc8 m_keys_state[256] = {};
		uc8 m_old_keys_state[256] = {};
		Point m_old_mouse_pos;
		bool m_first_time = true;
	};
}

