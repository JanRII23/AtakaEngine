#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/TextureBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3D/Math/Matrix4x4.h>
#include <DX3D/Graphics/ResourceManager/TextureManager/Texture.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc): GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferredContext Failed.");
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	f32 fColor[] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(swapChain.m_rtv.Get(), fColor);
	m_context->ClearDepthStencilView(swapChain.m_dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_context->OMSetRenderTargets(1, &rtv, swapChain.m_dsv.Get());
}

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	m_context->IASetInputLayout(pipeline.m_layout.Get());
	m_context->VSSetShader(pipeline.m_vs.Get(), nullptr, 0);
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto stride = buffer.m_vertexSize;
	auto buf = buffer.m_buffer.Get();
	auto offset = 0u;
	m_context->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<f32>(size.width);
	vp.Height = static_cast<f32>(size.height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_context->RSSetViewports(1, &vp);
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->Draw(vertexCount, startVertexLocation);
}

void dx3d::DeviceContext::drawIndexedTriangleList(ui32 index_count, ui32 start_vertex_index, ui32 start_index_location)
{
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void dx3d::DeviceContext::setConstantBuffer(const ConstantBuffer& buffer, constant cc)
{
	auto buf = buffer.m_buffer.Get();

	m_context->UpdateSubresource(buf, NULL, NULL, &cc, NULL, NULL);
	m_context->VSSetConstantBuffers(0, 1, &buf);
	m_context->PSSetConstantBuffers(0, 1, &buf);
}

void dx3d::DeviceContext::setTextureBuffer(const TextureBuffer& buffer, constant cc, TexturePtr texture)
{
	auto buf = buffer.m_buffer.Get();

	m_context->UpdateSubresource(buf, NULL, NULL, &cc, NULL, NULL);
	m_context->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
	m_context->PSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void dx3d::DeviceContext::setIndexBuffer(const IndexBuffer& buffer)
{
	m_context->IASetIndexBuffer(buffer.m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

dx3d::constant dx3d::DeviceContext::update(QuadPositionAttr attr, Matrix4x4 m_world_cam, f32 delta_time) const noexcept
{
	constant cc;
	//RECT rc{ 0, 0, size.width, size.height };

	Matrix4x4 temp;
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(attr.m_light_rot_y);

	attr.m_light_rot_y += 0.707f * delta_time;

	cc.m_light_direction = m_light_rot_matrix.getZDirection();

	//cc.m_world.setScaleVector3D(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.setTranslationVector3D(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5, 0), m_delta_pos));

	//cc.m_world *= temp;

	// NOTE: old setup #1
	//cc.m_world.setIdentity();

	//cc.m_world.setScaleVector3D(Vector3D(attr.m_scale_cube, attr.m_scale_1cube, attr.m_scale_cube));

	////temp.setRotationZ(attr.m_delta_scale);
	//temp.setRotationZ(0.0f);
	//cc.m_world *= temp;

	////temp.setRotationY(attr.m_delta_scale);
	//temp.setRotationY(attr.m_rot_y);
	//cc.m_world *= temp;

	////temp.setRotationX(attr.m_delta_scale);
	//temp.setRotationX(attr.m_rot_x);
	//cc.m_world *= temp;
	//NOTE: old setup #2

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(attr.m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(attr.m_rot_y);
	world_cam *= temp;

	cc.m_world.setIdentity();

	temp.setIdentity();
	temp.setScaleVector3D(Vector3D(attr.m_scale_cube, attr.m_scale_cube, attr.m_scale_cube));
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(attr.m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(attr.m_rot_x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslationVector3D(Vector3D(0, 0, 5));
	cc.m_world *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (attr.m_current_forward * 0.3f);

	new_pos = new_pos + world_cam.getXDirection() * (attr.m_current_rightward * 0.3f); 

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	// NOTE: old setup #1
	//cc.m_view.setIdentity();
	//NOTE: old setup #2
	 
	cc.m_view = world_cam;

	//NOTE: setting an override for now, but ideally needs to be tied to window size set by the user (main.cpp pretty sure 1280, 720) is the window size
	/*cc.m_proj.setOrthoLH(
		2.0f,
		2.0f,
		-4.0f,
		4.0f
	);*/

	//cc.m_proj.setOrthoLH(
	//	((rc.right - rc.left) / 10.0f) + std::abs(widthExtra),
	//	((rc.bottom - rc.top) / 10.0f) + std::abs(heightExtra),
	//	-4.0f,
	//	4.0f
	//);


	//NOTE: Rect struct setup in such a way where width = right & bottom = height
	int width = (attr.size.width - attr.size.left);
	int height = (attr.size.height - attr.size.top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	return cc;
}
