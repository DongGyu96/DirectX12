#pragma once
#include "Base.h"
class CObject_Mgr;
class CScene :public CBase
{
protected:
	CScene(ID3D12Device* pGraphic_Device);
	virtual	~CScene() = default;
public:
	virtual HRESULT		Ready_Scene();
	virtual _int		Update_Scene(const _float& fTimeDelta);
	virtual _int		LastUpdate_Scene(const _float& fTimeDelta);
	virtual void		Render_Scene();
protected:
	ID3D12Device*		m_pGraphic_Device = nullptr;
private:
	CObject_Mgr*		m_pObjectMgr = nullptr;
public:
	virtual void		Free();
};

