#pragma once
#include <DX3D/Graphics/ResourceManager/Resource.h>
#include <d3d11.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>


namespace dx3d
{
	class Mesh: public Resource
	{
	public:
		Mesh(const wchar_t* full_path, GraphicsDevice& device);
		~Mesh();
		const VertexBufferPtr& getVertexBuffer();
		const IndexBufferPtr& getIndexBuffer();
	private:
		VertexBuffer m_vertex_buffer;
		IndexBuffer m_index_buffer;
		ID3D11Device* m_device = nullptr;
		friend class DeviceContext;
	};
}

 
