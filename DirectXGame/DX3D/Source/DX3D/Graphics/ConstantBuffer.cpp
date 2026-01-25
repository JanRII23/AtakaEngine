#include <DX3D/Graphics/ConstantBuffer.h>

dx3d::ConstantBuffer::ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc, RenderSystem* system) : GraphicsResource(gDesc), m_system(system)
{
	if (!desc.buffer) DX3DLogThrowInvalidArg("No buffer provided.");
	if (!desc.size_buffer) DX3DLogThrowInvalidArg("No buffer size provided.");

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = desc.size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = desc.buffer;

	//TODO: 19:06
	//m_system->creatBu

	DX3DGraphicsLogThrowOnFail(m_device.CreateBuffer(
		&buff_desc, &init_data, &m_buffer
	), "ConstantBuffer CreateBuffer Failed.");
}
