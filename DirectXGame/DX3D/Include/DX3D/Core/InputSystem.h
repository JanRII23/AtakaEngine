#pragma once
#include <DX3D/Core/InputListener.h>
#include <DX3D/Core/Common.h>
#include <map>
#include <DX3D/Math/Point.h>

namespace dx3d
{
	class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();

		void update();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);

		static InputSystem* get();
	private:
		std::map<InputListener*, InputListener*> m_map_listeners;
		uc8 m_keys_state[256] = {};
		uc8 m_old_keys_state[256] = {};
		Point m_old_mouse_pos;
		bool m_first_time = true;
	};
}

