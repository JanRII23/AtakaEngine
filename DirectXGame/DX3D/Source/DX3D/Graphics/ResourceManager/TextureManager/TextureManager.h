#pragma once
#include <DX3D/Graphics/ResourceManager/ResourceManager.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h>

namespace dx3d
{
	class TextureManager: public ResourceManager
	{
	public:
		TextureManager();
		~TextureManager();
		TexturePtr createTextureFromFile(const wchar_t* file_path, GraphicsDevice& device);
	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path, GraphicsDevice& device);
	};
}


