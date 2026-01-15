#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>
#include <DX3D/Core/InputSystem.h>

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

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	InputSystem::get()->addListener(this);

	const Vertex vertexList[] =
	{
		//FRONT
		{ {-0.5f, -0.5f, -0.5f}, {1,0,0,1}, {0,1,0,1} }, // 0 front-bottom-left
		{ {-0.5f,  0.5f, -0.5f}, {0,1,0,1}, {0,0,1,1} }, // 1 front-top-left
		{ { 0.5f,  0.5f, -0.5f}, {0,0,1,1}, {1,0,0,1} }, // 2 front-top-right
		{ { 0.5f, -0.5f, -0.5f}, {0,0,1,1}, {1,0,0,1} }, // 3 front-bottom-right

		//BACK
		{ {-0.5f, -0.5f,  0.5f}, {1,0,0,1}, {0,1,0,1} }, // 4 back-bottom-left
		{ {-0.5f,  0.5f,  0.5f}, {0,1,0,1}, {0,0,1,1} }, // 5 back-top-left
		{ { 0.5f,  0.5f,  0.5f}, {0,0,1,1}, {1,0,0,1} }, // 6 back-top-right
		{ { 0.5f, -0.5f,  0.5f}, {0,0,1,1}, {1,0,0,1} }  // 7 back-bottom-right
	};

	/*const Vertex vertexList[] =
	{
		{ { -0.5f, -0.5f, 0.0f }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 } },
		{ { -0.5f, 0.5f, 0.0f }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 } },
		{ { 0.5f, 0.5f, 0.0f }, { 0, 0, 1, 1 }, { 1, 0, 0, 1 } },

		{ { 0.5f, 0.5f, 0.0f }, { 0, 0, 1, 1 }, { 1, 0, 0, 1 } },
		{ { 0.5f, -0.5f, 0.0f }, { 1, 0, 1, 1 }, { 1, 0, 0, 1 } },
		{ { -0.5f, -0.5f, 0.0f }, { 1, 0, 0, 1 }, { 0, 0, 1, 1 } }
	};*/
	
	constant cc;
	cc.m_time = 0;
	m_cb = device.createConstantBuffer({ &cc, sizeof(constant) });

	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vertex)});

	i32 index_list[] =
	{
		// FRONT
		0,1,2, 2,3,0,
		// BACK
		7,6,5, 5,4,7,
		// TOP
		1,5,6, 6,2,1,
		// BOTTOM
		0,3,7, 7,4,0,
		// RIGHT
		3,2,6, 6,7,3,
		// LEFT
		0,4,5, 5,1,0
	};

	m_ib = device.createIndexBuffer({ index_list , std::size(index_list)});
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
	InputSystem::get()->update();

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	
	context.setViewportSize(swapChain.getSize());

	QuadPositionAttr attr = { swapChain.getSize(), m_delta_pos, m_delta_scale, m_rot_x, m_rot_y };
	auto cc = context.updateQuadPosition(attr);

	auto& cb = *m_cb;
	context.setConstantBuffer(cb, cc);

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);

	auto& mb = *m_ib;
	context.setIndexBuffer(mb);

	//context.drawTriangleList(vb.getVertexListSize(), 0u); -> DRAWS A TRIANGLE
	context.drawIndexedTriangleList(mb.getSizeIndexList(), 0u, 0u);

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
	case ('W'): m_rot_x += 3.14f * m_delta_time; break;
	case ('S'): m_rot_x -= 3.14f * m_delta_time; break;
	case('A'): m_rot_y += 3.14f * m_delta_time; break;
	case('D'): m_rot_y -= 3.14f * m_delta_time; break;
	default: break;
	}
}

void dx3d::GraphicsEngine::onKeyUp(int key)
{
	/*switch (key) {
	case ('W'): m_rot_x += 3.14f * m_delta_time; break;
	case ('S'): m_rot_x -= 3.14f * m_delta_time; break;
	case('A'): m_rot_y += 3.14f * m_delta_time; break;
	case('D'): m_rot_y -= 3.14f * m_delta_time; break;
	}*/
}

void dx3d::GraphicsEngine::onMouseMove(const Point& delta_mouse_pos)
{
	m_rot_x -= delta_mouse_pos.m_y * m_delta_time;
	m_rot_y -= delta_mouse_pos.m_x * m_delta_time;
}

void dx3d::GraphicsEngine::onLeftMouseDown(const Point& mouse_pos)
{
	//TODO: seems to not work as expected??
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
