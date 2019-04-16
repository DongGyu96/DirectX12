#include "stdafx.h"
#include "Scene.h"
#include "Object_Mgr.h"

CScene::CScene(ID3D12Device * pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
	, m_pObjectMgr(CObject_Mgr::GetInstance())
{
	m_pGraphic_Device->AddRef();
	m_pObjectMgr->AddRef();
}

HRESULT CScene::Ready_Scene()
{
	return S_OK;
}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	if (nullptr == m_pObjectMgr)
		return -1;

	return m_pObjectMgr->Update_GameObject_Manager(fTimeDelta);
}

_int CScene::LastUpdate_Scene(const _float & fTimeDelta)
{
	if (nullptr == m_pObjectMgr)
		return -1;

	return m_pObjectMgr->LastUpdate_GameObject_Manager(fTimeDelta);
}

void CScene::Render_Scene()
{
}

void CScene::Free()
{
	Safe_Release(m_pObjectMgr);
	Safe_Release(m_pGraphic_Device);
}
