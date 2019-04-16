#pragma once
#include "Base.h"

#include "Component_Mgr.h"
class CScene;
class CGameObject;
class CObject_Mgr;
class CComponent;
class CManagement :public CBase
{
	_DECLARE_SINGLETON(CManagement)
private:
	CManagement();
	virtual ~CManagement() = default;
public:
	HRESULT		SetUp_ScenePointer(CScene* pNewScenePointer);
	_int		Update_Management(const _float& fTimeDelta);
	void		Render_Management();
	static void Release_Engine();
public:
	HRESULT		Ready_Management(const _uint& iNumScene);
	HRESULT		Add_Prototype_GameObject(const _tchar* pGameObjectTag, CGameObject* pGameObject);
	HRESULT		Add_GameObjcetToLayer(const _tchar* pProtoTag, const _uint& iSceneID, const _tchar* pLayerTag, CGameObject** ppCloneObject = nullptr);
	HRESULT		Clear_Layers(const _uint& iSceneID);
public:
	HRESULT		Add_Prototype_Component(const _uint& iSceneID, const _tchar* pComponentTag, CComponent* pComponent);
	CComponent* Clone_Component(const _uint& iSceneID, const _tchar* pComponentTag);
private:
	CScene*			m_pScene = nullptr;
	CObject_Mgr*	m_pObjectMgr = nullptr;
	CComponent_Mgr*	m_pComponentMgr = nullptr;
public:
	virtual void Free();
};

