#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h> 
#include <DirectXTex.h>
#include <DX3D/Graphics/GraphicsDevice.h>

//TODO: need to figure out some of this architecture refactoring
dx3d::Texture::Texture(const wchar_t* full_path, GraphicsDevice& device): Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

	m_device = device.getD3DDevice();

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(m_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		m_device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
	}
	else 
	{
		throw std::exception("Texture not created successfully");
	}

}

dx3d::Texture::~Texture()
{
	m_texture->Release();
}
