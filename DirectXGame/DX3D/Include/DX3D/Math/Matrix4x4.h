#pragma once
#include <DX3D/Core/Core.h>
#include <memory>
#include <DX3D/Math/Vector3D.h>
#include <DX3D/Math/Vec3.h>
#include <cmath>


namespace dx3d
{
	class Matrix4x4
	{
	public:
		Matrix4x4()
		{
		}
		
		void setIdentity()
		{
			::memset(m_mat, 0, sizeof(float) * 16);
			m_mat[0][0] = 1;
			m_mat[1][1] = 1;
			m_mat[2][2] = 1;
			m_mat[3][3] = 1;
		}

		void setTranslationVector3D(const Vector3D& translation)
		{
			setIdentity();
			m_mat[3][0] = translation.m_x;
			m_mat[3][1] = translation.m_y;
			m_mat[3][2] = translation.m_z;
		}

		void setScaleVector3D(const Vector3D& scale)
		{
			setIdentity();
			m_mat[0][0] = scale.m_x;
			m_mat[1][1] = scale.m_y;
			m_mat[2][2] = scale.m_z;
		}

		void setRotationX(f32 x)
		{
			m_mat[1][1] = std::cosf(x);
			m_mat[1][2] = std::sinf(x);
			m_mat[2][1] = -std::sinf(x);
			m_mat[2][2] = std::cosf(x);
		}

		void setRotationY(f32 y)
		{
			m_mat[0][0] = std::cosf(y);
			m_mat[0][2] = -std::sinf(y);
			m_mat[2][0] = std::sinf(y);
			m_mat[2][2] = std::cosf(y);
		}

		void setRotationZ(f32 z)
		{
			m_mat[0][0] = std::cosf(z);
			m_mat[0][1] = std::sinf(z);
			m_mat[1][0] = -std::sinf(z);
			m_mat[1][1] = std::cosf(z);
		}

		void setOrthoLH(f32 width, f32 height, f32 near_plane, f32 far_plane)
		{
			setIdentity();
			m_mat[0][0] = 2.0f / width;
			m_mat[3][1] = 2.0f / height;
			m_mat[3][2] = 1.0f / (far_plane - near_plane);
			m_mat[3][2] = -(near_plane / (far_plane - near_plane));
		}

		void operator *=(const Matrix4x4& matrix)
		{
			Matrix4x4 out;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					out.m_mat[i][j] =
						m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
						m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
				}
			}

			::memcpy(m_mat, out.m_mat, sizeof(float) * 16);
		}

		void setTranslationVec3(const Vec3& translation)
		{
			setIdentity();
			m_mat[3][0] = translation.x;
			m_mat[3][1] = translation.y;
			m_mat[3][2] = translation.z;
		}

		~Matrix4x4()
		{
		}
	public:
		float m_mat[4][4] = {};
	};
}