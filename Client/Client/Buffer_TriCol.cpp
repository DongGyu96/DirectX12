#include "stdafx.h"
#include "Buffer_TriCol.h"

CBuffer_TriCol::CBuffer_TriCol(ID3D12Device * pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CBuffer_TriCol::CBuffer_TriCol(const CBuffer_TriCol & rhs)
	: CVIBuffer(rhs)
	, m_VertexBufferView(rhs.m_VertexBufferView)
{
}

HRESULT CBuffer_TriCol::Ready_VIBuffer()
{
	m_iVertices = 3;
	m_iStride = sizeof(VTXCOL);
	m_PrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	VTXCOL pVertices[4];
	pVertices[0] = VTXCOL(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f));
	pVertices[1] = VTXCOL(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f));
	pVertices[2] = VTXCOL(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	
	CDevice::GetInstance()->Begin();
	m_pVertexBuffer = ::CreateBufferResource(m_pGraphic_Device, CDevice::GetInstance()->GetList(), pVertices,
		m_iStride * m_iVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pVertexUploadBuffer);
	CDevice::GetInstance()->End();



	m_VertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
	m_VertexBufferView.StrideInBytes = m_iStride;
	m_VertexBufferView.SizeInBytes = m_iStride * m_iVertices;


	return S_OK;
}

void CBuffer_TriCol::Render_VIBuffer()
{
	CDevice::GetInstance()->GetList()->IASetPrimitiveTopology(m_PrimitiveTopology);
	CDevice::GetInstance()->GetList()->IASetVertexBuffers(m_iSlot, 1, &m_VertexBufferView);
	CDevice::GetInstance()->GetList()->DrawInstanced(m_iVertices, 1, m_iOffset, 0);
}

CBuffer_TriCol * CBuffer_TriCol::Create(ID3D12Device * pGraphic_Device)
{
	CBuffer_TriCol* pInstance = new CBuffer_TriCol(pGraphic_Device);
	if (FAILED(pInstance->Ready_VIBuffer()))
		Safe_Release(pInstance);
	return pInstance;
}

CComponent * CBuffer_TriCol::Clone_Component()
{
	return new CBuffer_TriCol(*this);
}

void CBuffer_TriCol::Free()
{
	if (m_pVertexUploadBuffer)
		m_pVertexUploadBuffer->Release();
	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();
	CVIBuffer::Free();
}
