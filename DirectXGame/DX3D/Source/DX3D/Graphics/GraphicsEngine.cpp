#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
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

	const Vertex vertexList[] =
	{
		{ { -0.5f, -0.5f, 0.0f }, { -0.32f, -0.11f, 0.0f }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 }},
		{ { -0.5f, 0.5f, 0.0f }, { -0.11f, 0.78f, 0.0f }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 }},
		{ { 0.5f, 0.5f, 0.0f }, { 0.75f, -0.73f, 0.0f }, { 0, 0, 1, 1 }, { 1, 0, 0, 1 }},

		{ { 0.5f, 0.5f, 0.0f }, { 0.88f, 0.77f, 0.0f }, { 0, 0, 1, 1 }, { 1, 0, 0, 1 }},
		{ { 0.5f, -0.5f, 0.0f }, { -0.25f, 0.43f, 0.0f}, { 1, 0, 1, 1 }, { 1, 0, 0, 1 }},
		{ { -0.5f, -0.5f, 0.0f }, { -0.32f, -0.11f, 0.0f}, { 1, 0, 0, 1 }, { 0, 0, 1, 1 }}
	};

	constant cc;
	cc.m_time = 0;
	m_cb = device.createConstantBuffer({ &cc, sizeof(constant) });

	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vertex)});
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
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	
	context.setViewportSize(swapChain.getSize());

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f) {
		m_delta_pos = 0;
	}

	m_delta_scale += m_delta_time / 2.0f;

	auto& cb = *m_cb;
	context.setConstantBuffer(cb, swapChain.getSize(), m_delta_pos, m_delta_scale);

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}
