#pragma once
#include "Base.h"
class CLayer;
class CGameObject;
class CObject_Mgr:public CBase
{
	_DECLARE_SINGLETON(CObject_Mgr)
private:
	CObject_Mgr();
	virtual ~CObject_Mgr()=default;
public:
	HRESULT		Reserve_Object_Manager(const _uint& iNumScene);
	HRESULT		Add_Prototype_GameObject(const _tchar* pGameObjectTag, CGameObject* pGameObject);
	HRESULT		Add_GameObjectToLayer(const _tchar* pProtoTag, const _uint& iSceneID, const _tchar* pLayerTag, CGameObject** ppCloneObject);
	_int		Update_GameObject_Manager(const _float& fTimeDelta);
	_int		LastUpdate_GameObject_Manager(const _float& fTimeDelta);
	HRESULT		Clear_Layers(const _uint& iSceneID);
private:
	map<const _tchar*, CGameObject*>			m_mapPrototype;
	typedef map<const _tchar*, CGameObject*>	MAPPROTOTYPE;
private:
	map<const _tchar*, CLayer*>*				m_pMapLayers = nullptr;
	typedef map<const _tchar*, CLayer*>			MAPLAYERS;
private:
	_uint										m_iNumScene = 0;
private:
	CGameObject*	Find_Prototype(const _tchar* pGameObectTag);
	CLayer*			Find_Layer(const _uint& iSceneID, const _tchar* pLayerTag);
public:
	virtual void	Free();
};

