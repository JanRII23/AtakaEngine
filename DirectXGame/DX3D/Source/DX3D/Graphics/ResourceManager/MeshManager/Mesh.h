#pragma once
#include <DX3D/Graphics/ResourceManager/Resource.h>
#include <d3d11.h>

namespace dx3d
{
	class Mesh: public Resource
	{
	public:
		Mesh(const wchar_t* full_path, GraphicsDevice& device);
		~Mesh();
	private:
		ID3D11Device* m_device = nullptr;
		friend class DeviceContext;
	};
}

 
