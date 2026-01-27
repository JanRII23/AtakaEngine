#pragma once
#include <unordered_map>
#include <string>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/ResourceManager/Resource.h>

namespace dx3d
{
	class ResourceManager
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();

		ResourcePtr createResourceFromFile(const wchar_t* file_path);
	
	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;

	private:
		std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
	};
}

