#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h> 
#include <DirectXTex.h>
#include <DX3D/Graphics/GraphicsDevice.h>

dx3d::Texture::Texture(const wchar_t* full_path, GraphicsDevice& device): Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

	m_device = device.getD3DDevice();

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(m_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		if (FAILED(res))
		{
			throw std::exception("Texture not created successfully");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		D3D11_SAMPLER_DESC sampler_desc = {};
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = (UINT)image_data.GetMetadata().mipLevels;

		res = m_device->CreateSamplerState(&sampler_desc, &m_sampler_state);

		if (FAILED(res))
		{
			throw std::exception("Texture not created successfully");
		}

		res = m_device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);

		if (FAILED(res))
		{
			throw std::exception("Texture not created successfully");
		}
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
