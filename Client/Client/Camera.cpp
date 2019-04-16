#include "stdafx.h"
#include "Camera.h"
#include "Input.h"


CCamera::CCamera(ID3D12Device * pGraphic_Device)
	: CGameObject(pGraphic_Device)
	, m_pInput(CInput::GetInstance())
{
	m_pInput->AddRef();
}

CCamera::CCamera(const CCamera & rhs)
	: CGameObject(rhs)
	, m_tCameraDesc(rhs.m_tCameraDesc)
	, m_tProjDesc(rhs.m_tProjDesc)
	, m_matProj(rhs.m_matProj)
	, m_matView(rhs.m_matView)
	, m_pInput(rhs.m_pInput)
{
	m_pInput->AddRef();
}

HRESULT CCamera::Ready_Prototype()
{
	m_matProj = Matrix::Identity();
	m_matView = Matrix::Identity();


	ZeroMemory(&m_tProjDesc, sizeof(PROJDESC));
	ZeroMemory(&m_tCameraDesc, sizeof(CAMERADESC));
	return S_OK;
}

HRESULT CCamera::Ready_GameObject()
{
	m_pTransform = CTransform::Create(m_pGraphic_Device);
	if (nullptr == m_pTransform)
		return E_FAIL;

	if (FAILED(Add_Component(L"Com_Transform", m_pTransform)))
		return E_FAIL;

	return S_OK;
}

_int CCamera::Update_GameObject(const _float & fTimeDelta)
{
	return _int();
}

_int CCamera::LastUpdate_GameObject(const _float & fTimeDelta)
{
	return _int();
}

void CCamera::Render_GameObject()
{
}

HRESULT CCamera::SetUp_CameraProjDesc(const CAMERADESC & CameraDesc, const PROJDESC & ProjDesc)
{
	m_tCameraDesc = CameraDesc;
	m_tProjDesc = ProjDesc;
	SetUp_ViewProjMatrieces();
	return S_OK;
}

void CCamera::Invalidate_ViewProjMatrix()
{
	m_matView = m_pTransform->Get_Matrix_Inverse();
	CDevice::GetInstance()->SetViewMatrix(m_matView);
	CDevice::GetInstance()->SetProjectionMatrix(m_matProj);
}

HRESULT CCamera::SetUp_ViewProjMatrieces()
{
	_vec3		vLook;
	vLook = Vector3::Subtract(m_tCameraDesc.vAt, m_tCameraDesc.vEye);
	vLook = Vector3::Normalize(vLook);

	_vec3		vRight;
	vRight = Vector3::CrossProduct(m_tCameraDesc.vAxisY, vLook, false);
	vRight = Vector3::Normalize(vRight);

	_vec3		vUp;
	vUp = Vector3::CrossProduct(vLook, vRight);
	vUp = Vector3::Normalize(vUp);

	m_pTransform->Set_StateInfo(CTransform::STATE_RIGHT, &vRight);
	m_pTransform->Set_StateInfo(CTransform::STATE_UP, &vUp);
	m_pTransform->Set_StateInfo(CTransform::STATE_LOOK, &vLook);
	m_pTransform->Set_StateInfo(CTransform::STATE_POSITION, &m_tCameraDesc.vEye);

	m_matProj._11 = (1.f / tan(m_tProjDesc.fFovY * 0.5f)) / m_tProjDesc.fAspect;
	m_matProj._22 = 1.f / tan(m_tProjDesc.fFovY * 0.5f);
	m_matProj._33 = m_tProjDesc.fFar / (m_tProjDesc.fFar - m_tProjDesc.fNear);
	m_matProj._43 = (m_tProjDesc.fFar * m_tProjDesc.fNear) / (m_tProjDesc.fFar - m_tProjDesc.fNear) * -1.f;
	m_matProj._34 = 1.f;
	m_matProj._44 = 0.0f;

	Invalidate_ViewProjMatrix();
	return S_OK;
}

void CCamera::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pInput);
	CGameObject::Free();
}
