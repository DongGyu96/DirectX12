#include "stdafx.h"
#include "Scene_Logo.h"
#include "Management.h"
#include "Back_Logo.h"
#include "Camera_Debug.h"

CScene_Logo::CScene_Logo(ID3D12Device * pGraphic_Device)
	:CScene(pGraphic_Device)
{

}

HRESULT CScene_Logo::Ready_Scene()
{
	if (FAILED(Ready_Prototype_GameObject()))
		return E_FAIL;
	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(L"Layer_BackGround")))
		return E_FAIL;
	if (FAILED(Ready_Layer_Camera(L"Layer_Camera")))
		return E_FAIL;


	return S_OK;
}

_int CScene_Logo::Update_Scene(const _float & fTimeDelta)
{
	return CScene::Update_Scene(fTimeDelta);
}

_int CScene_Logo::LastUpdate_Scene(const _float & fTimeDelta)
{
	return CScene::LastUpdate_Scene(fTimeDelta);
}

void CScene_Logo::Render_Scene()
{
	int a = 0;
}

HRESULT CScene_Logo::Ready_Prototype_GameObject()
{
	CManagement* pManagement = CManagement::GetInstance();

	if (nullptr == pManagement)
		return E_FAIL;

	pManagement->AddRef();

	if (FAILED(pManagement->Add_Prototype_GameObject(L"GameObject_Back_Logo", CBack_Logo::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(pManagement->Add_Prototype_GameObject(L"GameObject_Camera_Debug",CCamera_Debug::Create(m_pGraphic_Device))))
		return E_FAIL;

	Safe_Release(pManagement);
	return S_OK;
}

HRESULT CScene_Logo::Ready_Prototype_Component()
{

	CManagement* pManangement = CManagement::GetInstance();
	if (nullptr == pManangement)
		return E_FAIL;

	pManangement->AddRef();

	if (FAILED(pManangement->Add_Prototype_Component(SCENE_LOGO, L"Component_Buffer_TriCol",
		CBuffer_TriCol::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pManangement->Add_Prototype_Component(SCENE_LOGO, L"Component_Buffer_Cube",
		CBuffer_Cube::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(pManangement->Add_Prototype_Component(SCENE_LOGO, L"Component_Buffer_Terrain",
		CBuffer_Terrain::Create(m_pGraphic_Device, 100, 100,1.f))))
		return E_FAIL;

	if (FAILED(pManangement->Add_Prototype_Component(SCENE_LOGO, L"Component_Shader_Default",
		CShader::Create(m_pGraphic_Device, L"../Shader/Shader_Default.hlsl", "VSMain", "PSMain"))))
		return E_FAIL;

	Safe_Release(pManangement);
	return S_OK;
}


HRESULT CScene_Logo::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CManagement* pManagement = CManagement::GetInstance();

	if (nullptr == pManagement)
		return E_FAIL;

	pManagement->AddRef();

	if (FAILED(pManagement->Add_GameObjcetToLayer(L"GameObject_Back_Logo", SCENE_LOGO, pLayerTag)))
		return E_FAIL;

	Safe_Release(pManagement);
	return S_OK;
}

HRESULT CScene_Logo::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CManagement* pManagement = CManagement::GetInstance();
	if (nullptr == pManagement)
		return E_FAIL;

	pManagement->AddRef();

	CCamera_Debug*		pCamera_Debug = nullptr;

	if (FAILED(pManagement->Add_GameObjcetToLayer(L"GameObject_Camera_Debug", SCENE_LOGO, pLayerTag, (CGameObject**)&pCamera_Debug)))
		return E_FAIL;

	CAMERADESC		tCameraDesc;
	ZeroMemory(&tCameraDesc, sizeof(CAMERADESC));
	tCameraDesc.vEye = _vec3(0.f, 10.f, -5.f);
	tCameraDesc.vAt = _vec3(0.f, 0.f, 1.f);
	tCameraDesc.vAxisY = _vec3(0.f, 1.f, 0.f);
	PROJDESC		tProjDesc;
	ZeroMemory(&tProjDesc, sizeof(tProjDesc));
	tProjDesc.fFovY = XMConvertToRadians(60.f);
	tProjDesc.fAspect = _float(WINCX) / WINCY;
	tProjDesc.fNear = 0.2f;
	tProjDesc.fFar = 500.f;

	
	
	if (FAILED(pCamera_Debug->SetUp_CameraProjDesc(tCameraDesc, tProjDesc)))
		return E_FAIL;

	Safe_Release(pManagement);
	return S_OK;
}

CScene_Logo * CScene_Logo::Create(ID3D12Device * pGraphic_Device)
{
	CScene_Logo* pInstance = new CScene_Logo(pGraphic_Device);
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Release(pInstance);
	return pInstance;
}

void CScene_Logo::Free()
{
	CScene::Free();
}
