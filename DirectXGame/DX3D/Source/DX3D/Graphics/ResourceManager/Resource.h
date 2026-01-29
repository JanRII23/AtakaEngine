#pragma once
#include <string>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>

namespace dx3d
{
	class Resource
	{
	public:
		Resource(const wchar_t* full_path);
		~Resource();
	protected:
		std::wstring m_full_path;
	};
}

