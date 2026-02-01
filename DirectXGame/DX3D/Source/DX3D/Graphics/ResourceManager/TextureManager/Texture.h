#pragma once
#include <DX3D/Graphics/ResourceManager/Resource.h>
#include <d3d11.h>

namespace dx3d
{
	class Texture: public Resource
	{
	public:
		Texture(const wchar_t* full_path, GraphicsDevice& device);
		~Texture();
	private:
		ID3D11Device* m_device = nullptr;
		ID3D11Resource* m_texture = nullptr;
	};
}

