#include <DX3D/Graphics/ResourceManager/MeshManager/MeshManager.h>
#include <DX3D/Graphics/ResourceManager/MeshManager/Mesh.h>

using namespace dx3d;

dx3d::MeshManager::MeshManager() : ResourceManager()
{
}

dx3d::MeshManager::~MeshManager()
{
}

MeshPtr dx3d::MeshManager::createMeshFromFile(const wchar_t* file_path, GraphicsDevice& device)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path, device));
}

dx3d::Resource* dx3d::MeshManager::createResourceFromFileConcrete(const wchar_t* file_path, GraphicsDevice& device)
{
	Mesh* mesh = nullptr;
	try {
		mesh = new Mesh(file_path, device);
	}
	catch (...) {}

	return mesh;
}
