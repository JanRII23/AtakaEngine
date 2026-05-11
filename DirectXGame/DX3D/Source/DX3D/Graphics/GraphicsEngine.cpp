#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/TextureBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>
#include <DX3D/Core/InputSystem.h>
#include <DX3D/Math/Matrix4x4.h>
#include <DX3D/Graphics/ResourceManager/MeshManager/Mesh.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base), m_old_delta(0), m_new_delta(0), m_delta_time(0.0f), m_delta_pos(0.0f), m_delta_scale(0.0f)
{
	/*SwapChainPtr sc{};

	{
		auto sys = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_logger });
		sc = sys->createSwapChain({});
	}*/

	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);

	if (!shaderStream) DX3DLogThrowError("Failed to open shader file.");

	std::string shaderFileData {
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	auto vs = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "VSMain", ShaderType::VertexShader });
	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "PSMain", ShaderType::PixelShader });
	auto vsSig = device.createVertexShaderSignature({ vs });

	auto m_sky_ps = compileShaderType("DX3D/Assets/Shaders/SkyBoxShader.hlsl", device,
		"psmain", ShaderType::SkyBoxShader);

	m_mesh_manager = new MeshManager();
	if (!m_mesh_manager) DX3DLogThrowError("Failed to create Mesh Manager.");

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	constexpr char vertexMeshLayoutShaderFilePath[] = "DX3D/Assets/Shaders/VertexMeshLayoutShader.hlsl";
	std::ifstream vertexMeshLayoutShaderStream(vertexMeshLayoutShaderFilePath);

	if (!vertexMeshLayoutShaderStream) DX3DLogThrowError("Failed to create vertex mesh layout shader file.");
	std::string vertexMeshLayoutShaderFileData{
		std::istreambuf_iterator<char>(vertexMeshLayoutShaderStream),
		std::istreambuf_iterator<char>()
	};

	auto vertexMeshLayoutShaderSourceCode = vertexMeshLayoutShaderFileData.c_str();
	auto vertexMeshLayoutShaderSourceCodeSize = vertexMeshLayoutShaderFileData.length();

	auto vm = device.compileShader({ vertexMeshLayoutShaderFilePath, vertexMeshLayoutShaderSourceCode, vertexMeshLayoutShaderSourceCodeSize, "vsmain", ShaderType::VertexMeshLayoutShader });
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	m_sky_pipeline = device.createGraphicsPipelineState({ *vsSig, *m_sky_ps });

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	m_tex_manager = new TextureManager();
	if (!m_tex_manager) DX3DLogThrowError("Failed to create Texture Manager.");
	

	m_wood_tex = m_tex_manager->createTextureFromFile(L"DX3D/Assets/Textures/brick.png", *m_graphicsDevice);

	m_sky_tex = m_tex_manager->createTextureFromFile(L"DX3D/Assets/Textures/sky.jpg", *m_graphicsDevice);

	m_mesh = getMeshManager()->createMeshFromFile(L"DX3D/Assets/Meshes/suzanne.obj", *m_graphicsDevice);

	m_sky_mesh = getMeshManager()->createMeshFromFile(L"DX3D/Assets/Meshes/sphere.obj", *m_graphicsDevice);

	m_world_cam.setTranslation(Vector3D(0, 0, 3));

	//TODO: note the transformation is still needs a bit more refinement before its smooth completely
	Vec3 position_list[] =
	{
		//FRONT
		{-0.5f, -0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},

		//BACK
		{-0.5f, -0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f}
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f, 0.0f) },
		{ Vector2D(0.0f, 1.0f) },
		{ Vector2D(1.0f, 0.0f) },
		{ Vector2D(1.0f, 1.0f) }
	};

	const Vertex vertexList[] =
	{
		{ position_list[0], texcoord_list[1] },
		{ position_list[1], texcoord_list[0] },
		{ position_list[2], texcoord_list[2] },
		{ position_list[3], texcoord_list[3] },

		{ position_list[7], texcoord_list[1] },
		{ position_list[6], texcoord_list[0] },
		{ position_list[5], texcoord_list[2] },
		{ position_list[4], texcoord_list[3] },

		{ position_list[1], texcoord_list[1] },
		{ position_list[5], texcoord_list[0] },
		{ position_list[6], texcoord_list[2] },
		{ position_list[2], texcoord_list[3] },

		{ position_list[0], texcoord_list[1] },
		{ position_list[3], texcoord_list[0] },
		{ position_list[7], texcoord_list[2] },
		{ position_list[4], texcoord_list[3] },

		{ position_list[3], texcoord_list[1] },
		{ position_list[2], texcoord_list[0] },
		{ position_list[6], texcoord_list[2] },
		{ position_list[7], texcoord_list[3] },

		{ position_list[0], texcoord_list[1] },
		{ position_list[4], texcoord_list[0] },
		{ position_list[5], texcoord_list[2] },
		{ position_list[1], texcoord_list[3] }
	};

	//const Vertex vertexList[] =
	//{
	//	//FRONT
	//	{ {-0.5f, -0.5f, -0.5f}, {1, 0, 0, 1}, {0, 1, 0, 1} }, // 0 front-bottom-left
	//	{ {-0.5f,  0.5f, -0.5f}, {0, 1, 0, 1}, {0, 0, 1, 1} }, // 1 front-top-left
	//	{ { 0.5f,  0.5f, -0.5f}, {0, 0, 1, 1}, {1, 0, 0, 1} }, // 2 front-top-right
	//	{ { 0.5f, -0.5f, -0.5f}, {0, 0, 1, 1}, {1, 0, 0, 1} }, // 3 front-bottom-right

	//	//BACK
	//	{ {-0.5f, -0.5f,  0.5f}, {1, 0, 0, 1}, {0, 1, 0, 1} }, // 4 back-bottom-left
	//	{ {-0.5f,  0.5f,  0.5f}, {0, 1, 0, 1}, {0, 0, 1, 1} }, // 5 back-top-left
	//	{ { 0.5f,  0.5f,  0.5f}, {0, 0, 1, 1}, {1, 0, 0, 1} }, // 6 back-top-right
	//	{ { 0.5f, -0.5f,  0.5f}, {0, 0, 1, 1}, {1, 0, 0, 1} }  // 7 back-bottom-right
	//};
	
	constant cc;
	m_cb = device.createConstantBuffer({ &cc, sizeof(constant) });
	m_tex = device.createTextureBufferPtr({ &cc, sizeof(constant) });
	m_sky_cb = device.createConstantBuffer({ &cc, sizeof(constant) });

	i32 index_list[] =
	{
		// FRONT
		0,1,2,
		2,3,0,
		// BACK
		4,5,6,
		6,7,4,
		// TOP
		8,9,10,
		10,11,8,
		// BOTTOM
		12,13,14,
		14,15,12,
		// RIGHT
		16,17,18,
		18,19,16,
		// LEFT
		20,21,22,
		22,23,20
	};
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	InputSystem::get()->update(swapChain.getSize());

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	
	context.setViewportSize(swapChain.getSize());

	QuadPositionAttr attr = { swapChain.getSize(), m_delta_pos, m_delta_scale, m_rot_x, m_rot_y, m_scale_cube, m_forward, m_current_forward, m_rightward, m_current_rightward, m_current_light_rot_y };

	MatrixCams cameras = {
		m_world_cam,
		m_world_cam,
		m_world_cam
	};

	attr.m_current_forward = m_current_forward;
	attr.m_current_rightward = m_current_rightward;
	attr.m_current_light_rot_y = m_current_light_rot_y;
	
	// COMPUTE TRANSORMATION MATRICES
	auto cc = context.update(attr, cameras);

	//RENDER MODEL
	context.setGraphicsPipelineState(*m_pipeline);
	drawMesh(m_mesh, cc, context, m_wood_tex);

	//RENDER SKYBOX/SPHERE
	auto cc_sky = context.updateSkyBox(attr, cameras);
	context.setGraphicsPipelineState(*m_sky_pipeline);
	drawMesh(m_sky_mesh, cc_sky, context, m_sky_tex);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}

void dx3d::GraphicsEngine::updateTime()
{
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f) {
		m_delta_pos = 0;
	}

	m_delta_scale += m_delta_time / 0.15f;


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

	if (m_auto_rotate)
	{
		m_rot_y += 1.0f * m_delta_time;
	}
}

void dx3d::GraphicsEngine::updateTargetPosition()
{
	static float move_acceleration = 2.0f; // bigger = faster response

	m_current_forward += (m_forward - m_current_forward) * move_acceleration * m_delta_time;

	m_current_rightward += (m_rightward - m_current_rightward) * move_acceleration * m_delta_time;
}

void dx3d::GraphicsEngine::updateLightPosition()
{
	m_current_light_rot_y += 0.707f * m_delta_time;
}

void dx3d::GraphicsEngine::onFocus()
{
	InputSystem::get()->addListener(this);
}

void dx3d::GraphicsEngine::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void dx3d::GraphicsEngine::onKeyDown(int key)
{
	switch (key) {
	case ('W'): 
		//m_rot_x += 3.14f * m_delta_time; 
		m_forward = 5.0f;
		break;
	case ('S'): 
		//m_rot_x -= 3.14f * m_delta_time; 
		m_forward = -20.f;
		break;
	case('A'): 
		//m_rot_y += 3.14f * m_delta_time; 
		m_rightward = 8.0f;
		break;
	case('D'): 
		//m_rot_y -= 3.14f * m_delta_time; 
		m_rightward = -8.0f;
		break;
	default: break;
	}
}

void dx3d::GraphicsEngine::onKeyUp(int key)
{
	switch (key)
	{
	case ('W'):
	case ('S'):
		m_forward = 0.0f;
		break;
	case ('A'):
	case ('D'):
		m_rightward = 0.0f;
		break;
	default: break;
	}
}

void dx3d::GraphicsEngine::onMouseMove(const Point& mouse_pos, const Rect& size)
{
	int width = size.width - size.left;
	int height = size.height - size.top;

	constexpr float mouse_sensitivity = 0.0050f;

	//if (m_middle_mouse_down)
	//{
	//	
	//}

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * mouse_sensitivity * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * mouse_sensitivity * 0.1f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void dx3d::GraphicsEngine::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void dx3d::GraphicsEngine::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void dx3d::GraphicsEngine::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void dx3d::GraphicsEngine::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void dx3d::GraphicsEngine::onMiddleMouseDown(const Point& mouse_pos)
{
	m_middle_mouse_down = true;
	m_auto_rotate = true;
}

void dx3d::GraphicsEngine::onMiddleMouseUp(const Point& mouse_pos)
{
	m_middle_mouse_down = false;
	m_auto_rotate = false;
}

TextureManager* dx3d::GraphicsEngine::getTextureManager() noexcept
{
	return m_tex_manager;
}

MeshManager* dx3d::GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void dx3d::GraphicsEngine::drawMesh(const MeshPtr& mesh, auto cc, DeviceContext& context, const TexturePtr& texType)
{
	auto& cb = *m_cb;
	context.setConstantBuffer(cb, cc);

	auto& tex = *m_tex;
	context.setTextureBuffer(tex, cc, texType);

	auto& vb = *mesh->getVertexBuffer();
	context.setVertexBuffer(vb);

	auto& mb = *mesh->getIndexBuffer();
	context.setIndexBuffer(mb);

	context.drawIndexedTriangleList(mb.getSizeIndexList(), 0u, 0u);
}

ShaderBinaryPtr dx3d::GraphicsEngine::compileShaderType(const char* shaderFilePath, GraphicsDevice& device, const char* shaderEntryPoint, ShaderType shaderType)
{
	std::ifstream shaderStream(shaderFilePath);

	if (!shaderStream) DX3DLogThrowError("Failed to open shader file.");

	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	return device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, shaderEntryPoint, shaderType });
}
