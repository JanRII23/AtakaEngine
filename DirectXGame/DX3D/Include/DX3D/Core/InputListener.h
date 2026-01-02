#pragma once

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
	};
}