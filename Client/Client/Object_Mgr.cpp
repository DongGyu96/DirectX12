#include "stdafx.h"
#include "Object_Mgr.h"
#include "Layer.h"

_IMPLEMENT_SINGLETON(CObject_Mgr)
CObject_Mgr::CObject_Mgr()
{
}



HRESULT CObject_Mgr::Reserve_Object_Manager(const _uint & iNumScene)
{
	if (nullptr != m_pMapLayers)
		return E_FAIL;

	m_pMapLayers = new MAPLAYERS[iNumScene];

	m_iNumScene = iNumScene;

	return S_OK;
}

HRESULT CObject_Mgr::Add_Prototype_GameObject(const _tchar * pGameObjectTag, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	if (nullptr != Find_Prototype(pGameObjectTag))
		return E_FAIL;

	m_mapPrototype.insert(MAPPROTOTYPE::value_type(pGameObjectTag, pGameObject));
	return S_OK;
}

HRESULT CObject_Mgr::Add_GameObjectToLayer(const _tchar * pProtoTag, const _uint & iSceneID, const _tchar * pLayerTag,CGameObject** ppCloneObject)
{
	if (nullptr == m_pMapLayers)
		return E_FAIL;

	if (m_iNumScene <= iSceneID)
		return E_FAIL;

	CGameObject* pPrototype = nullptr;

	pPrototype = Find_Prototype(pProtoTag);

	if (nullptr == pPrototype)
		return E_FAIL;

	CGameObject*	pGameObject = pPrototype->Clone_GameObject();
	if (nullptr == pGameObject)
		return E_FAIL;

	if (nullptr != ppCloneObject)
		*ppCloneObject = pGameObject;

	CLayer*		pLayer = Find_Layer(iSceneID, pLayerTag);
	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;

		if (FAILED(pLayer->Add_Object(pGameObject)))
			return E_FAIL;

		m_pMapLayers[iSceneID].insert(MAPLAYERS::value_type(pLayerTag, pLayer));
	}
	else
		if (FAILED(pLayer->Add_Object(pGameObject)))
			return E_FAIL;


	return S_OK;
}

_int CObject_Mgr::Update_GameObject_Manager(const _float & fTimeDelta)
{
	if (nullptr == m_pMapLayers)
		return -1;

	for (size_t i = 0; i < m_iNumScene; i++)
	{
		for (auto& Pair : m_pMapLayers[i])
		{
			if (nullptr != Pair.second)
			{
				if (Pair.second->Update_Object(fTimeDelta) & 0x80000000)
					return -1;
			}
		}
	}

	return _int();
}

_int CObject_Mgr::LastUpdate_GameObject_Manager(const _float & fTimeDelta)
{
	if (nullptr == m_pMapLayers)
		return -1;

	for (size_t i = 0; i < m_iNumScene; i++)
	{
		for (auto& Pair : m_pMapLayers[i])
		{
			if (nullptr != Pair.second)
			{
				if (Pair.second->LastUpdate_Object(fTimeDelta) & 0x80000000)
					return -1;
			}
		}
	}
	return _int();
}

HRESULT CObject_Mgr::Clear_Layers(const _uint & iSceneID)
{
	if (nullptr == m_pMapLayers)
		return E_FAIL;

	if (m_iNumScene <= iSceneID)
		return E_FAIL;

	for (auto& Pair : m_pMapLayers[iSceneID])
		Safe_Release(Pair.second);

	m_pMapLayers[iSceneID].clear();

	return NOERROR;
}

CGameObject * CObject_Mgr::Find_Prototype(const _tchar * pGameObectTag)
{
	auto	iter = find_if(m_mapPrototype.begin(), m_mapPrototype.end(), CFinder_Tag(pGameObectTag));

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}

CLayer * CObject_Mgr::Find_Layer(const _uint & iSceneID, const _tchar * pLayerTag)
{
	auto	iter = find_if(m_pMapLayers[iSceneID].begin(), m_pMapLayers[iSceneID].end(), CFinder_Tag(pLayerTag));

	if (iter == m_pMapLayers[iSceneID].end())
		return nullptr;

	return iter->second;
}

void CObject_Mgr::Free()
{
	for (size_t i = 0; i < m_iNumScene; i++)
	{
		for (auto& Pair : m_pMapLayers[i])
			Safe_Release(Pair.second);

		m_pMapLayers[i].clear();
	}

	Safe_Delete_Array(m_pMapLayers);

	for (auto& Pair : m_mapPrototype)
		Safe_Release(Pair.second);

	m_mapPrototype.clear();
}
