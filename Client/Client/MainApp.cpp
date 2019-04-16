#include "stdafx.h"
#include "MainApp.h"
#include "Management.h"
#include "Scene_Logo.h"
#include "Input.h"


CMainApp::CMainApp()
	:m_pManagement(CManagement::GetInstance())
{
	m_pManagement->AddRef();
}
HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(CInput::GetInstance()->Ready_Input_Device(g_hInst, g_hWnd)))
		return E_FAIL;

	m_pGraphic_Device = CDevice::GetInstance()->GetDevice();
	m_pGraphic_Device->AddRef();

	if (FAILED(m_pManagement->Ready_Management(SCENE_END)))
		return E_FAIL;
	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;
	if (FAILED(Ready_Start_Scene(SCENE_LOGO)))
		return E_FAIL;

	return S_OK;
}

_int CMainApp::Update_MainApp(const _float & fTimeDelta)
{

	m_fTimeAcc += fTimeDelta;
	CInput::GetInstance()->SetUp_InputState();
	return m_pManagement->Update_Management(fTimeDelta);
}

void CMainApp::Render_MainApp()
{
	if (nullptr == m_pManagement)
		return;
	if (nullptr == m_pGraphic_Device)
		return;

	//뷰포트랑 가위사각형 세팅해주기

	if (nullptr != m_pRenderer)
		m_pRenderer->Render_RenderGroup();

	m_pManagement->Render_Management();
	++m_dwRenderCnt;

	
	if (m_fTimeAcc >= 1.f)
	{
		wsprintf(m_szFPS, L"FPS:%d", m_dwRenderCnt);
		m_dwRenderCnt = 0;
		m_fTimeAcc = 0.f;
	}

	SetWindowText(g_hWnd, m_szFPS);
}

HRESULT CMainApp::Ready_Start_Scene(SCENEID eSceneID)
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	CScene*			pScene = nullptr;

	switch (eSceneID)
	{
	case SCENE_LOGO:
		pScene = CScene_Logo::Create(m_pGraphic_Device);
		break;
	case SCENE_STAGE:
		break;
	}
	if (nullptr == pScene)
		return E_FAIL;

	if (FAILED(m_pManagement->SetUp_ScenePointer(pScene)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CMainApp::Ready_Prototype_Component()
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Prototype_Component(SCENE_STATIC, L"Component_Transform", CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pManagement->Add_Prototype_Component(SCENE_STATIC, L"Component_Renderer", m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pManagement->Add_Prototype_Component(SCENE_STATIC, L"Component_Combine", m_pCombine = CCombine::Create(m_pGraphic_Device))))
		return E_FAIL;

	m_pRenderer->AddRef();
	m_pCombine->AddRef();
	return NOERROR;
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
		Safe_Release(pInstance);
	return pInstance;
}

void CMainApp::Free()
{	
	Safe_Release(m_pCombine);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pManagement);
	Safe_Release(m_pGraphic_Device);

	CManagement::Release_Engine();
}
