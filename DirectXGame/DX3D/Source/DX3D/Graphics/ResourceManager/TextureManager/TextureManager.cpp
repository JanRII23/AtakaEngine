#include <DX3D/Graphics/ResourceManager/TextureManager/TextureManager.h>
#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h>

using namespace dx3d;

dx3d::TextureManager::TextureManager() : ResourceManager()
{
}

dx3d::TextureManager::~TextureManager()
{
}

TexturePtr dx3d::TextureManager::createTextureFromFile(const wchar_t* file_path, GraphicsDevice& device)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path, device));
}

dx3d::Resource* dx3d::TextureManager::createResourceFromFileConcrete(const wchar_t* file_path, GraphicsDevice& device)
{
	Texture* tex = nullptr;
	try {
		tex = new Texture(file_path, device);
	}
	catch (...) {}

	return tex;
}
