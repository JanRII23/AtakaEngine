#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	/*SwapChainPtr sc{};

	{
		auto sys = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_logger });
		sc = sys->createSwapChain({});
	}*/

	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() const noexcept
{
	return *m_graphicsDevice;
}
