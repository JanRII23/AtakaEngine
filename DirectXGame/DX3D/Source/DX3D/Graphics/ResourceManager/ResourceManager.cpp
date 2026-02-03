#include <DX3D/Graphics/ResourceManager/ResourceManager.h>
#include <filesystem>

dx3d::ResourceManager::ResourceManager()
{
}

dx3d::ResourceManager::~ResourceManager()
{
}

dx3d::ResourcePtr dx3d::ResourceManager::createResourceFromFile(const wchar_t* file_path, GraphicsDevice& device)
{
	std::wstring full_path = std::filesystem::absolute(file_path).wstring();

	auto it = m_map_resources.find(full_path);

	if (it != m_map_resources.end())
		return it->second;

	Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str(), device);

	if (raw_res)
	{
		ResourcePtr res(raw_res);
		m_map_resources[full_path] = res;
		return res;
	}

	return nullptr;
}
