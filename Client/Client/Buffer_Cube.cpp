#include "stdafx.h"
#include "Buffer_Cube.h"



CBuffer_Cube::CBuffer_Cube(ID3D12Device * pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CBuffer_Cube::CBuffer_Cube(const CBuffer_Cube & rhs)
	:CVIBuffer(rhs)
	,m_VertexBufferView(rhs.m_VertexBufferView)
	,m_IndexBufferView(rhs.m_IndexBufferView)
{
	
}

HRESULT CBuffer_Cube::Ready_VIBuffer()
{
	m_iVertices = 8;
	m_iStride = sizeof(VTXCOL);
	m_PrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	VTXCOL pVertices[8];
	pVertices[0] = VTXCOL(XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[1] = VTXCOL(XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[2] = VTXCOL(XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[3] = VTXCOL(XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[4] = VTXCOL(XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[5] = VTXCOL(XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[6] = VTXCOL(XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[7] = VTXCOL(XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));


	m_iIndices = 36;

	_uint	indicies[36]{};
	indicies[0] = 1; indicies[1] = 5; indicies[2] = 6;
	indicies[3] = 1; indicies[4] = 6; indicies[5] = 2;

	indicies[6] = 4; indicies[7] = 0; indicies[8] = 3;
	indicies[9] = 4; indicies[10] = 3; indicies[11] = 7;

	indicies[12] = 4; indicies[13] = 5; indicies[14] = 1;
	indicies[15] = 4; indicies[16] = 1; indicies[17] = 0;

	indicies[18] = 3; indicies[19] = 2; indicies[20] = 6;
	indicies[21] = 3; indicies[22] = 6; indicies[23] = 7;

	indicies[24] = 7; indicies[25] = 6; indicies[26] = 5;
	indicies[27] = 7; indicies[28] = 5; indicies[29] = 4;

	indicies[30] = 0; indicies[31] = 1; indicies[32] = 2;
	indicies[33] = 0; indicies[34] = 2; indicies[35] = 3;

	


	CDevice::GetInstance()->Begin();
	m_pVertexBuffer = ::CreateBufferResource(m_pGraphic_Device, CDevice::GetInstance()->GetList(), pVertices,
		m_iStride * m_iVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pVertexUploadBuffer);

	m_pIndexBuffer = ::CreateBufferResource(m_pGraphic_Device, CDevice::GetInstance()->GetList(), indicies,
		sizeof(_uint)*m_iIndices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pIndexUploadBuffer);


	CDevice::GetInstance()->End();



	m_VertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
	m_VertexBufferView.StrideInBytes = m_iStride;
	m_VertexBufferView.SizeInBytes = m_iStride * m_iVertices;

	m_IndexBufferView.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
	m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_IndexBufferView.SizeInBytes = sizeof(_uint) * m_iIndices;
	return S_OK;
}

void CBuffer_Cube::Render_VIBuffer()
{
	CDevice::GetInstance()->GetList()->IASetPrimitiveTopology(m_PrimitiveTopology);
	CDevice::GetInstance()->GetList()->IASetVertexBuffers(m_iSlot, 1, &m_VertexBufferView);
	CDevice::GetInstance()->GetList()->IASetIndexBuffer(&m_IndexBufferView);
	CDevice::GetInstance()->GetList()->DrawIndexedInstanced(m_iIndices, 1, 0, 0, 0);
}

CBuffer_Cube * CBuffer_Cube::Create(ID3D12Device * pGraphic_Device)
{
	CBuffer_Cube* pInstance = new CBuffer_Cube(pGraphic_Device);
	if (FAILED(pInstance->Ready_VIBuffer()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CBuffer_Cube::Clone_Component()
{
	return new CBuffer_Cube(*this);
}

void CBuffer_Cube::Free()
{
	if (m_pVertexUploadBuffer)
		m_pVertexUploadBuffer->Release();

	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();

	if (m_pIndexUploadBuffer)
		m_pIndexUploadBuffer->Release();

	if (m_pIndexBuffer)
		m_pIndexBuffer->Release();

	CVIBuffer::Free();
	
}
