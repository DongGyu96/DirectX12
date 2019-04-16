#pragma once
#include "Camera.h"
class CCamera_Debug :
	public CCamera
{
private:
	CCamera_Debug(ID3D12Device* pGraphic_Device);
	CCamera_Debug(const CCamera_Debug& rhs);
	virtual ~CCamera_Debug() = default;
public:
	virtual HRESULT			Ready_Prototype();
	virtual HRESULT			Ready_GameObject();
	virtual _int			Update_GameObject(const _float& fTimeDelta);
	virtual	_int			LastUpdate_GameObject(const _float& fTimeDelta);
	virtual void			Render_GameObject();
private:
	POINT					m_ptMouse;
public:
	static CCamera_Debug*	Create(ID3D12Device* pGraphic_Device);
	virtual	CGameObject*	Clone_GameObject();
	virtual void			Free();
};

