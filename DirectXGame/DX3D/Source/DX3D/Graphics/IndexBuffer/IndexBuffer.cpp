#include <DX3D/Graphics/IndexBuffer/IndexBuffer.h>

dx3d::IndexBuffer::IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc), m_size_list(desc.size_list)
{
	if (!desc.list_indices) DX3DLogThrowInvalidArg("No list indices provided.");
	if (!desc.size_list)  DX3DLogThrowInvalidArg("Size list indices must be non-zero");

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * desc.size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = desc.list_indices;

	DX3DGraphicsLogThrowOnFail(m_device.CreateBuffer(
		&buff_desc, &init_data, &m_buffer
	), "IndexBuffer CreateBuffer Failed.");
}

dx3d::ui32 dx3d::IndexBuffer::getSizeIndexList() const noexcept
{
	return m_size_list;
}
