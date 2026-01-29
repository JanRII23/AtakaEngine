#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h> 
#include <DirectXTex.h>

//TODO: need to figure out some of this architecture tho
dx3d::Texture::Texture(const wchar_t* full_path): Resource(full_path)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		//res = DirectX::CreateTexture()
	}
	else 
	{
		throw std::exception("Texture not created successfully");
	}

}

dx3d::Texture::~Texture()
{
}
