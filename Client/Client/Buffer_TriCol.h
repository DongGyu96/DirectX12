#pragma once
#include "VIBuffer.h"
class CBuffer_TriCol :
	public CVIBuffer
{
private:
	CBuffer_TriCol(ID3D12Device* pGraphic_Device);
	CBuffer_TriCol(const CBuffer_TriCol& rhs);
	virtual ~CBuffer_TriCol()=default;
public:
	HRESULT Ready_VIBuffer();
	void	Render_VIBuffer();
private:
	D3D12_VERTEX_BUFFER_VIEW	m_VertexBufferView;
public:
	static CBuffer_TriCol* Create(ID3D12Device* pGraphic_Device);
	virtual CComponent*		Clone_Component();
	virtual void			Free();
};
