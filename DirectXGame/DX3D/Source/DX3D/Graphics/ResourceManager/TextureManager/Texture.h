#pragma once
#include <DX3D/Graphics/ResourceManager/Resource.h>

namespace dx3d
{
	class Texture: public Resource
	{
	public:
		Texture(const wchar_t* full_path);
		~Texture();
	};
}

