#pragma once

namespace dx3d
{
	class IFocusListener
	{
	public:
		virtual ~IFocusListener() = default;
		virtual void onFocus() = 0;
		virtual void onKillFocus() = 0;
		virtual void onSize() {}
	};
}