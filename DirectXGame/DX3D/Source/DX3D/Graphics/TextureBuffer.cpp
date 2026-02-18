#include <DX3D/Graphics/TextureBuffer.h>

dx3d::TextureBuffer::TextureBuffer(const TextureBufferDesc& desc, const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	if (!desc.textureBuffer) DX3DLogThrowInvalidArg("No buffer provided.");
	if (!desc.size_buffer) DX3DLogThrowInvalidArg("No buffer size provided.");

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = desc.size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = desc.textureBuffer;

	DX3DGraphicsLogThrowOnFail(m_device.CreateBuffer(
		&buff_desc, &init_data, &m_buffer
	), "TextureBuffer CreateBuffer Failed.");
}
