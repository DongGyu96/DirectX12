#include "stdafx.h"
#include "Buffer_Terrain.h"


CBuffer_Terrain::CBuffer_Terrain(ID3D12Device * pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CBuffer_Terrain::CBuffer_Terrain(const CBuffer_Terrain & rhs)
	: CVIBuffer(rhs)
	, m_VertexBufferView(rhs.m_VertexBufferView)
	, m_IndexBufferView(rhs.m_IndexBufferView)
	, m_iNumVerticesX(rhs.m_iNumVerticesX)
	, m_iNumVerticesZ(rhs.m_iNumVerticesZ)
	, m_fInterval(rhs.m_fInterval)
{
}

HRESULT CBuffer_Terrain::Ready_VIBuffer(const _uint & iNumVerticesX, const _uint iNumVerticesZ, const _float & fInterval)
{
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;
	m_fInterval = fInterval;

	m_iVertices = m_iNumVerticesX * m_iNumVerticesZ;
	m_iStride = sizeof(VTXTEX);
	m_PrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	VTXTEX* pVertices = new VTXTEX[m_iVertices];

	for (size_t i = 0; i < iNumVerticesZ; i++)
	{
		for (size_t j = 0; j < iNumVerticesX; j++)
		{
			_uint      iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = _vec3(j * m_fInterval, 0.0f, i * m_fInterval);
			pVertices[iIndex].vTexUV = _vec2(j / (iNumVerticesX - 1.f) * 30.f, i / (iNumVerticesZ - 1.f) * 30.f);
		}
	}

	m_iIndices = (3 * ((m_iNumVerticesX * 2)*(m_iNumVerticesZ - 1)) + ((m_iNumVerticesZ - 1) - 1));
	//POLYGON32 *pIndices = new POLYGON32[m_iIndices];
	_uint* pIndices = new _uint[m_iIndices];

	ID3D12Resource*            m_pVertexBuffe;

	_uint         iPolygonIndex = 0;

	for (size_t i = 0; i < iNumVerticesZ - 1; ++i)
	{
		for (size_t j = 0; j < iNumVerticesX - 1; ++j)
		{
			size_t iIndex = i * iNumVerticesX + j;

			// ¿ì.»ó
			pIndices[iPolygonIndex] = iIndex + iNumVerticesX;
			pIndices[iPolygonIndex + 1] = iIndex + iNumVerticesX + 1;
			pIndices[iPolygonIndex + 2] = iIndex + 1;

			pIndices[iPolygonIndex + 3] = iIndex + iNumVerticesX;
			pIndices[iPolygonIndex + 4] = iIndex + 1;
			pIndices[iPolygonIndex + 5] = iIndex;


			iPolygonIndex += 6; // next quad
		}
	}




	CDevice::GetInstance()->Begin();
	m_pVertexBuffer = ::CreateBufferResource(m_pGraphic_Device, CDevice::GetInstance()->GetList(), pVertices,
		m_iStride * m_iVertices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pVertexUploadBuffer);



	m_pIndexBuffer = ::CreateBufferResource(m_pGraphic_Device, CDevice::GetInstance()->GetList(), pIndices,
		sizeof(_uint)*m_iIndices, D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pIndexUploadBuffer);
	CDevice::GetInstance()->End();

	m_VertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
	m_VertexBufferView.StrideInBytes = m_iStride;
	m_VertexBufferView.SizeInBytes = m_iStride * m_iVertices;

	m_IndexBufferView.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
	m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_IndexBufferView.SizeInBytes = sizeof(_uint) * m_iIndices;

	delete[] pVertices;
	delete[] pIndices;
	return S_OK;
}

void CBuffer_Terrain::Render_VIBuffer()
{
	CDevice::GetInstance()->GetList()->IASetPrimitiveTopology(m_PrimitiveTopology);
	CDevice::GetInstance()->GetList()->IASetVertexBuffers(m_iSlot, 1, &m_VertexBufferView);
	CDevice::GetInstance()->GetList()->IASetIndexBuffer(&m_IndexBufferView);
	CDevice::GetInstance()->GetList()->DrawIndexedInstanced(m_iIndices, 1, 0, 0, 0);
}

CBuffer_Terrain * CBuffer_Terrain::Create(ID3D12Device * pGraphic_Device, const _uint & iNumVerticesX, const _uint & iNumVerticesZ, const _float & fInterval)
{
	CBuffer_Terrain* pInstance = new CBuffer_Terrain(pGraphic_Device);
	if (FAILED(pInstance->Ready_VIBuffer(iNumVerticesX, iNumVerticesZ, fInterval)))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CBuffer_Terrain::Clone_Component()
{
	return new CBuffer_Terrain(*this);
}

void CBuffer_Terrain::Free()
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
