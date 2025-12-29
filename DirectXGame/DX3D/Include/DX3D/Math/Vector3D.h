#pragma once
#include <DX3D/Core/Core.h>

//NOTE: might NOT need this, checkout Vec3?
namespace dx3d
{
	class Vector3D
	{
	public:
		Vector3D() :m_x(0), m_y(0), m_z(0)
		{
		}
		Vector3D(f32 x, f32 y, f32 z) :m_x(x), m_y(y), m_z(z)
		{
		}
		Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
		{
		}
	public:
		f32 m_x, m_y, m_z;
	};
}