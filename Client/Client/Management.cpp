#include "stdafx.h"
#include "Management.h"
#include "Scene.h"

#include "Device.h"
#include "System.h"
#include "Timer_Mgr.h"
#include "Frame_Mgr.h"
#include "Object_Mgr.h"
#include "Component_Mgr.h"

_IMPLEMENT_SINGLETON(CManagement)
CManagement::CManagement()
	: m_pObjectMgr(CObject_Mgr::GetInstance())
	, m_pComponentMgr(CComponent_Mgr::GetInstance())
{
	m_pObjectMgr->AddRef();
	m_pComponentMgr->AddRef();
}
HRESULT CManagement::Ready_Management(const _uint & iNumScene)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	if (FAILED(m_pObjectMgr->Reserve_Object_Manager(iNumScene)))
		return E_FAIL;
	if (FAILED(m_pComponentMgr->Reserve_Component_Manager(iNumScene)))
		return E_FAIL;

	return S_OK;
}


HRESULT CManagement::SetUp_ScenePointer(CScene * pNewScenePointer)
{
	if (nullptr == pNewScenePointer)
		return E_FAIL;
	if (0 != Safe_Release(m_pScene))
		return E_FAIL;

	m_pScene = pNewScenePointer;
	m_pScene->AddRef();
	return S_OK;
}

_int CManagement::Update_Management(const _float& fTimeDelta)
{
	if (nullptr == m_pScene)
		return -1;
	_int iProcessCodes = 0;

	iProcessCodes = m_pScene->Update_Scene(fTimeDelta);
	if (iProcessCodes & 0x80000000)
		return iProcessCodes;

	iProcessCodes = m_pScene->LastUpdate_Scene(fTimeDelta);
	if (iProcessCodes & 0x80000000)
		return iProcessCodes;

	return _int(0);
}

void CManagement::Render_Management()
{
	if (nullptr == m_pScene)
		return;

	m_pScene->Render_Scene();
}



HRESULT CManagement::Add_Prototype_GameObject(const _tchar * pGameObjectTag, CGameObject * pGameObject)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	return m_pObjectMgr->Add_Prototype_GameObject(pGameObjectTag, pGameObject);
}

HRESULT CManagement::Add_GameObjcetToLayer(const _tchar * pProtoTag, const _uint & iSceneID, const _tchar * pLayerTag, CGameObject** ppCloneObject)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	return m_pObjectMgr->Add_GameObjectToLayer(pProtoTag, iSceneID, pLayerTag, ppCloneObject);
}

HRESULT CManagement::Clear_Layers(const _uint & iSceneID)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	return m_pObjectMgr->Clear_Layers(iSceneID);
}

HRESULT CManagement::Add_Prototype_Component(const _uint & iSceneID, const _tchar * pComponentTag, CComponent * pComponent)
{
	if (nullptr == m_pComponentMgr)
		return E_FAIL;


	return m_pComponentMgr->Add_Prototype_Component(iSceneID, pComponentTag, pComponent);
}

CComponent * CManagement::Clone_Component(const _uint & iSceneID, const _tchar * pComponentTag)
{
	if (nullptr == m_pComponentMgr)
		return nullptr;

	return m_pComponentMgr->Clone_Component(iSceneID, pComponentTag);
}

void CManagement::Release_Engine()
{
	_ulong			dwRefCnt = 0;

	if (dwRefCnt = CManagement::GetInstance()->DestroyInstance())
		_MSG_BOX("CManagement Release Failed");

	if (dwRefCnt = CObject_Mgr::GetInstance()->DestroyInstance())
		_MSG_BOX("CObject_Manager Release Failed");

	if (dwRefCnt = CSystem::GetInstance()->DestroyInstance())
		_MSG_BOX("CSystem Release Failed");

	if (dwRefCnt = CTimer_Mgr::GetInstance()->DestroyInstance())
		_MSG_BOX("CTimer_Manager Release Failed");

	if (dwRefCnt = CFrame_Mgr::GetInstance()->DestroyInstance())
		_MSG_BOX("CTimer_Manager Release Failed");

	if (dwRefCnt = CDevice::GetInstance()->DestroyInstance())
		_MSG_BOX("CGraphic_Device Release Failed");
}


void CManagement::Free()
{
	Safe_Release(m_pComponentMgr);
	Safe_Release(m_pObjectMgr);
	Safe_Release(m_pScene);
}
