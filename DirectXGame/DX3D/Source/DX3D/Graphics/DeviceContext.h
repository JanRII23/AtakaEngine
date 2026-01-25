#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Graphics/RenderResource.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Math/Matrix4x4.h>

namespace dx3d
{
	class DeviceContext final: public GraphicsResource, public RenderResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc, RenderSystem* system, const RenderResourceDesc& rDesc);
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setViewportSize(const Rect& size);
		void drawTriangleList(ui32 vertexCount, ui32 startVertexLocation);
		void drawIndexedTriangleList(ui32 index_count, ui32 start_vertex_index, ui32 start_index_location);
		void setConstantBuffer(const ConstantBuffer& buffer, constant cc);
		void setIndexBuffer(const IndexBuffer& buffer);
		constant update(QuadPositionAttr attr, Matrix4x4 m_world_cam) const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};
		RenderSystem* m_system = nullptr;

		friend class GraphicsDevice;
	};
}


