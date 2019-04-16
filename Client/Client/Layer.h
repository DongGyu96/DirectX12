#pragma once
#include "Base.h"
#include "GameObject.h"
class CLayer:public CBase
{
private:
	CLayer();
	virtual ~CLayer()=default;
public:
	HRESULT Add_Object(CGameObject* pGameObject);
	HRESULT Ready_Layer();
	_int	Update_Object(const _float& fTimeDelta);
	_int	LastUpdate_Object(const _float& fTimeDelta);
private:
	list<CGameObject*>			m_ObjectList;
	typedef list<CGameObject*>	OBJECTLIST;
public:
	static CLayer*	Create();
	virtual void	Free();
};

