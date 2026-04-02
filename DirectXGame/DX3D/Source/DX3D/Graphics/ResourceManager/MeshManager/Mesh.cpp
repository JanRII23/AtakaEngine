#include <DX3D/Graphics/ResourceManager/MeshManager/Mesh.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <windows.h>
#include <string>

#include <DX3D/Math/VertexMesh.h>

using namespace dx3d;

dx3d::Mesh::Mesh(const wchar_t* full_path, GraphicsDevice& device) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, full_path, -1, nullptr, 0, nullptr, nullptr);
	std::string inputfile(size_needed - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, full_path, -1, &inputfile[0], size_needed, nullptr, nullptr);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not create successfully");

	std::vector<VertexMesh> list_vertices;

	for (size_t s = 0; s < shapes.size(); s++) 
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++) 
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);
			}

			index_offset += num_face_verts;
		}
	}

	device.createVertexBuffer(&list_vertices[0], sizeof(VertexMesh), list_vertices.size(), );
}

dx3d::Mesh::~Mesh()
{
}
