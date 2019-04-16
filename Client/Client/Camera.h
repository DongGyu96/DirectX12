#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
class CCamera :
	public CGameObject
{
protected:
	CCamera(ID3D12Device* pGraphic_Device);
	CCamera(const CCamera& rhs);
	virtual ~CCamera() = default;
public:
	virtual HRESULT			Ready_Prototype();
	virtual HRESULT			Ready_GameObject();
	virtual _int			Update_GameObject(const _float& fTimeDelta);
	virtual _int			LastUpdate_GameObject(const _float& fTimeDelta);
	virtual void			Render_GameObject();
public:
	HRESULT					SetUp_CameraProjDesc(const CAMERADESC& CameraDesc, const PROJDESC& ProjDesc);
	void					Invalidate_ViewProjMatrix();
protected:
	CTransform*				m_pTransform = nullptr;
	_matrix					m_matView;
	CAMERADESC				m_tCameraDesc;
protected:
	_matrix					m_matProj;
	PROJDESC				m_tProjDesc;
private:
	HRESULT					SetUp_ViewProjMatrieces();
protected:
	CInput*					m_pInput = nullptr;
public:
	virtual	CGameObject*	Clone_GameObject()PURE;
	virtual void			Free();
};

