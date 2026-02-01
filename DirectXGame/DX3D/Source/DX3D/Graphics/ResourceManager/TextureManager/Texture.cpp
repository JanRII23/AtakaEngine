#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h> 
#include <DirectXTex.h>
#include <DX3D/Graphics/GraphicsDevice.h>

//TODO: need to figure out some of this architecture tho
dx3d::Texture::Texture(const wchar_t* full_path, GraphicsDevice& device): Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	m_device = device.getD3DDevice();

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(m_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);
	}
	else 
	{
		throw std::exception("Texture not created successfully");
	}

}

dx3d::Texture::~Texture()
{
}
