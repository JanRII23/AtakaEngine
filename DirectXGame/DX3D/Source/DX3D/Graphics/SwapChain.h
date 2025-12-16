#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class SwapChain final: public GraphicsResource
	{
	public:
		SwapChain(const GraphicsResourceDesc& desc);
	};
}
