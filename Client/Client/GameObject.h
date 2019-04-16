#pragma once
#include "Base.h"
class CGameObject :public CBase
{
protected:
	CGameObject(ID3D12Device* pGraphic_Device);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject()=default;
public:
	virtual HRESULT			Ready_GameObject();
	virtual _int			Update_GameObject(const _float& fTimeDelta);
	virtual	_int			LastUpdate_GameObject(const _float& fTimeDelta);
	virtual void			Render_GameObject();
protected:
	ID3D12Device*			m_pGraphic_Device = nullptr;
protected:
	map<const _tchar*, CComponent*>			m_mapComponent;
	typedef map<const _tchar*, CComponent*>	MAPCOMPONENT;
protected:
	HRESULT Add_Component(const _tchar* pComponentTag, CComponent* pComponent);
	CComponent* Find_Component(const _tchar* pComponentTag);
public:
	virtual CGameObject*	Clone_GameObject()PURE;
	virtual void			Free();
};

