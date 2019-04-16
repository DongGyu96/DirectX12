#pragma once
#include "Component.h"

class CShader;
class CCombine :
	public CComponent
{
private:
	CCombine(ID3D12Device* pGraphic_Device);
	CCombine(const CCombine& rhs);
	virtual ~CCombine()=default;
public:
	HRESULT Ready_Combine();
public:
	void	BuildObject(ID3D12Device* pGraphic_Device, CShader* pShader);
	void	ReleaseObject();
	bool	ProcessInput();
	void	Render(void** pBuffer);
public:
	HRESULT	SetUp_OnShader(XMFLOAT4X4 matWorld, XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
private:
	D3D12_RASTERIZER_DESC		CreateRaterizerState();
	D3D12_DEPTH_STENCIL_DESC	CreateDepthStencilState();
	D3D12_BLEND_DESC			CreateBlendState();
	D3D12_INPUT_LAYOUT_DESC		CreateInputLayout();
private:
	ID3D12RootSignature*		m_pRootSignature = nullptr;
	ID3D12PipelineState*		m_pPipiLine = nullptr;
public:
	ID3D12RootSignature*		GetRootSignature() { return m_pRootSignature; }
	ID3D12PipelineState*		GetPipeLine() { return m_pPipiLine; }


public:
	static CCombine*		Create(ID3D12Device* pGraphic_Device);
	virtual CComponent *	Clone_Component() override;
	virtual void			Free();
};

