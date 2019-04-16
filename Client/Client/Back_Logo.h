#pragma once
#include "GameObject.h"
class CTransform;
class CRenderer;
class CCombine;

class CBuffer_Terrain;
class CShader;
class CBack_Logo:public CGameObject
{
private:
	CBack_Logo(ID3D12Device* pGraphic_Device);
	CBack_Logo(const CBack_Logo& rhs);
	virtual ~CBack_Logo()=default;
public:
	virtual HRESULT Ready_Prototype();
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual _int	LastUpdate_GameObject(const _float& fTimeDelta);
	virtual void	Render_GameObject();
private:
	HRESULT Ready_Component();

private:
	CTransform*		m_pTransformCom = nullptr;
	CRenderer*		m_pRendererCom = nullptr;
	CBuffer_Terrain*	m_pBufferCom = nullptr;
	CCombine*		m_pCombineCom = nullptr;
	CShader*		m_pShader = nullptr;
	
public:
	static CBack_Logo*	Create(ID3D12Device* pGraphic_Device);
	virtual CGameObject* Clone_GameObject()override;
	virtual void	Free();
};

