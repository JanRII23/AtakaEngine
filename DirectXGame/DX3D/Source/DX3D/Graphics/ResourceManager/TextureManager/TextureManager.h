#pragma once
#include <DX3D/Graphics/ResourceManager/ResourceManager.h>

namespace dx3d
{
	class TextureManager: public ResourceManager
	{
	public:
		TextureManager();
		~TextureManager();
		virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
	};
}


