#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
	class DeviceContext final: public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setViewportSize(const Rect& size);
		void drawTriangleList(ui32 vertexCount, ui32 startVertexLocation);
		void drawIndexedTriangleList(ui32 index_count, ui32 start_vertex_index, ui32 start_index_location);
		void setConstantBuffer(const ConstantBuffer& buffer, const Rect& size, f32 m_delta_pos, f32 m_delta_scale);
		void setIndexBuffer(const IndexBuffer& buffer);
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class GraphicsDevice;
	};
}


