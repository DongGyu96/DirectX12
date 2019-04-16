#pragma once
#include "VIBuffer.h"
class CBuffer_Cube :
	public CVIBuffer
{
private:
	CBuffer_Cube(ID3D12Device*	pGraphic_Device);
	CBuffer_Cube(const CBuffer_Cube& rhs);
	virtual ~CBuffer_Cube()=default;
public:
	HRESULT Ready_VIBuffer();
	void	Render_VIBuffer();
private:
	D3D12_VERTEX_BUFFER_VIEW	m_VertexBufferView;
	D3D12_INDEX_BUFFER_VIEW		m_IndexBufferView;
public:
	static CBuffer_Cube* Create(ID3D12Device* pGraphic_Device);
	virtual CComponent*		Clone_Component();
	virtual void			Free();
};

