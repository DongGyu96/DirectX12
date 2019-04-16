#include "stdafx.h"
#include "VIBuffer.h"


CVIBuffer::CVIBuffer(ID3D12Device * pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_iVertices(rhs.m_iVertices)
	, m_iSlot(rhs.m_iSlot)
	, m_iStride(rhs.m_iStride)
	, m_iOffset(rhs.m_iOffset)

	, m_iIndices(rhs.m_iIndices)
	, m_iStartIndex(rhs.m_iStartIndex)
{

}

void CVIBuffer::Free()
{
	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();
	if (m_pVertexUploadBuffer)
		m_pVertexUploadBuffer->Release();
}
