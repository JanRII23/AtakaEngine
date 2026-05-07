#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>
#include <DX3D/Math/Matrix4x4.h>
#include <Windows.h>

namespace dx3d
{
	struct BaseDesc
	{
		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base;
		Rect size{};
	};

	struct DisplayDesc
	{
		WindowDesc window;
		GraphicsDevice& graphicsDevice;
	};

	struct GraphicsEngineDesc
	{
		BaseDesc base;
	};

	struct GraphicsDeviceDesc
	{
		BaseDesc base;
	};

	struct SwapChainDesc
	{
		void* winHandle{};
		Rect winSize{};
	};

	enum class ShaderType
	{
		VertexShader = 0,
		PixelShader,
		VertexMeshLayoutShader,
		SkyBoxShader
	};

	struct ShaderCompileDesc
	{
		const char* shaderSourceName{};
		const void* shaderSourceCode{};
		size_t shaderSourceCodeSize{};
		const char* shaderEntryPoint{};
		ShaderType shaderType{};
	};

	struct VertexShaderSignatureDesc
	{
		const ShaderBinaryPtr& vsBinary;
	};

	struct BinaryData
	{
		const void* data{};
		size_t dataSize{};
	};

	struct GraphicsPipelineStateDesc
	{
		const VertexShaderSignature& vs;
		const ShaderBinary& ps;
	};

	struct VertexBufferDesc
	{
		const void* vertexList{};
		ui32 vertexListSize{};
		ui32 vertexSize{};
		void* shader_byte_code = nullptr;
		size_t size_shader = 0;
	};

	struct ConstantBufferDesc
	{
		const void* buffer{};
		ui32 size_buffer;
	};

	struct IndexBufferDesc
	{
		const void* list_indices{};
		ui32 size_list{};
	};

	struct TextureBufferDesc
	{
		const void* textureBuffer{};
		ui32 size_buffer;
	};

	struct QuadPositionAttr
	{
		const Rect& size;
		f32 m_delta_pos;
		f32 m_delta_scale;
		f32 m_rot_x;
		f32 m_rot_y;
		f32 m_scale_cube;
		f32 m_forward;
		f32 m_current_forward;
		f32 m_rightward;
		f32 m_current_rightward;
		f32 m_light_rot_y;
		f32 m_current_light_rot_y;
	};

	struct MatrixCams
	{
		Matrix4x4 m_world_cam;
		Matrix4x4 m_view_cam;
		Matrix4x4 m_proj_cam;
	};

	struct GameDesc
	{
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};

	_declspec(align(16))
	struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		Vector4D m_light_direction;
		Vector4D m_camera_position;
	};
}