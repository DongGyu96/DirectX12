#include "stdafx.h"
#include "Back_Logo.h"
#include "Management.h"


CBack_Logo::CBack_Logo(ID3D12Device * pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CBack_Logo::CBack_Logo(const CBack_Logo & rhs)
	:CGameObject(rhs)
{
}

HRESULT CBack_Logo::Ready_Prototype()
{
	return S_OK;
}

HRESULT CBack_Logo::Ready_GameObject()
{
	if (FAILED(Ready_Component()))
		return E_FAIL;
	
	m_pShader->Compile_Shader();
	m_pCombineCom->BuildObject(m_pGraphic_Device, m_pShader);

	

	m_pTransformCom->SetUp_Speed(10.f, XMConvertToRadians(60.f));
	return S_OK;
}

_int CBack_Logo::Update_GameObject(const _float & fTimeDelta)
{
	//m_pTransformCom->Rotation_Y(fTimeDelta);
	return _int();
}

_int CBack_Logo::LastUpdate_GameObject(const _float & fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return -1;
	if (FAILED(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONEALPHA, this)))
		return -1;
	return _int();
}

void CBack_Logo::Render_GameObject()
{
	if (nullptr == m_pBufferCom || nullptr == m_pCombineCom)
		return;
	_matrix matWorld = m_pTransformCom->Get_Matrix();

	_matrix matView = CDevice::GetInstance()->GetViewMatrix();
	_matrix matProj = CDevice::GetInstance()->GetProjectionMatrix();
	m_pCombineCom->SetUp_OnShader(matWorld, matView, matProj);

	
	m_pBufferCom->Render_VIBuffer();
}

HRESULT CBack_Logo::Ready_Component()
{
	CManagement* pManagement = CManagement::GetInstance();
	if (nullptr == pManagement) 
		return E_FAIL;
	pManagement->AddRef();
	m_pTransformCom = (CTransform*)pManagement->Clone_Component(SCENE_STATIC, L"Component_Transform");
	if (FAILED(Add_Component(L"Com_Transform", m_pTransformCom)))
		return E_FAIL;
	m_pRendererCom = (CRenderer*)pManagement->Clone_Component(SCENE_STATIC, L"Component_Renderer");
	if (FAILED(Add_Component(L"Com_Renderer", m_pRendererCom)))
		return E_FAIL;
	m_pBufferCom = (CBuffer_Terrain*)pManagement->Clone_Component(SCENE_LOGO, L"Component_Buffer_Terrain");
	if (FAILED(Add_Component(L"Com_Buffer", m_pRendererCom)))
		return E_FAIL;
	m_pCombineCom = (CCombine*)pManagement->Clone_Component(SCENE_STATIC, L"Component_Combine");
	if (FAILED(Add_Component(L"Com_Combine", m_pRendererCom)))
		return E_FAIL;
	m_pShader = (CShader*)pManagement->Clone_Component(SCENE_LOGO, L"Component_Shader_Default");
	if (FAILED(Add_Component(L"Com_Shader", m_pRendererCom)))
		return E_FAIL;
	Safe_Release(pManagement);
	return S_OK;
}

CBack_Logo * CBack_Logo::Create(ID3D12Device * pGraphic_Device)
{
	CBack_Logo*	pInstance = new CBack_Logo(pGraphic_Device);
	if (FAILED(pInstance->Ready_Prototype()))
	{
		MessageBox(0, L"CBack_Logo Created Failed", L"System Error", MB_OK);
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBack_Logo::Clone_GameObject()
{
	CBack_Logo*	pInstance = new CBack_Logo(*this);
	if (FAILED(pInstance->Ready_GameObject()))
	{
		MessageBox(0, L"CBack_Logo Created Failed", L"System Error", MB_OK);
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBack_Logo::Free()
{
	m_pCombineCom->ReleaseObject();
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pCombineCom);
	Safe_Release(m_pBufferCom);
	CGameObject::Free();
}
