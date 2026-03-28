#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Core/InputSystem.h>

dx3d::Game::Game(const GameDesc& desc) :
	Base({ *std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger)
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ {m_logger, desc.windowSize}, m_graphicsEngine->getGraphicsDevice() });

	m_display->setGraphicsEngine(m_graphicsEngine.get());

	try {
		InputSystem::create();
	} catch (...) { DX3DLogInfo("Game Failed to Initialize."); }

	DX3DLogInfo("Game Initialized.");
}


dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
	InputSystem::release();
}

void dx3d::Game::onInternalUpdate()
{
	m_graphicsEngine->updateTime();
	m_graphicsEngine->updateTargetPosition();
	m_graphicsEngine->render(m_display->getSwapChain());
}

