#include "stdafx.h"
#include "Camera_Debug.h"

CCamera_Debug::CCamera_Debug(ID3D12Device * pGraphic_Device)
	:CCamera(pGraphic_Device)
{
}

CCamera_Debug::CCamera_Debug(const CCamera_Debug & rhs)
	:CCamera(rhs)
{
}

HRESULT CCamera_Debug::Ready_Prototype()
{
	if (FAILED(CCamera::Ready_Prototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CCamera_Debug::Ready_GameObject()
{
	if (FAILED(CCamera::Ready_GameObject()))
		return E_FAIL;

	m_pTransform->SetUp_Speed(10.f, XMConvertToRadians(90.f));

	D3D12_VIEWPORT ViewPort = CDevice::GetInstance()->GetViewPort();


	m_ptMouse.x = ViewPort.Width / 2;
	m_ptMouse.y = ViewPort.Height / 2;
	ClientToScreen(g_hWnd, &m_ptMouse);

	return S_OK;
}

_int CCamera_Debug::Update_GameObject(const _float & fTimeDelta)
{
	SetCursorPos(m_ptMouse.x, m_ptMouse.y);

	if (nullptr == m_pInput)
		return -1;

	if (m_pInput->Get_DIKeyState(DIK_D) & 0x80)
	{
		m_pTransform->Go_Right(fTimeDelta);
	}
	if (m_pInput->Get_DIKeyState(DIK_A) & 0x80)
	{
		m_pTransform->Go_Left(fTimeDelta);
	}

	if (m_pInput->Get_DIKeyState(DIK_W) & 0x80)
	{
		m_pTransform->Go_Straight(fTimeDelta);
	}

	if (m_pInput->Get_DIKeyState(DIK_S) & 0x80)
	{
		m_pTransform->BackWard(fTimeDelta);
	}
	_long	MouseMove = 0;

	if (MouseMove = m_pInput->Get_DIMouseMove(CInput::DIM_X))
	{
		m_pTransform->Rotation_Y(MouseMove * fTimeDelta*0.3f);
	}
	if (MouseMove = m_pInput->Get_DIMouseMove(CInput::DIM_Y))
	{
		m_pTransform->Rotation_Axis(XMConvertToRadians(MouseMove) * -fTimeDelta*3, m_pTransform->Get_StateInfo(CTransform::STATE_RIGHT));
	}

	return _int();
}

_int CCamera_Debug::LastUpdate_GameObject(const _float & fTimeDelta)
{
	Invalidate_ViewProjMatrix();
	return _int();
}

void CCamera_Debug::Render_GameObject()
{
}

CCamera_Debug * CCamera_Debug::Create(ID3D12Device * pGraphic_Device)
{
	CCamera_Debug* pInstance = new CCamera_Debug(pGraphic_Device);
	if (FAILED(pInstance->Ready_Prototype()))
		Safe_Release(pInstance);
	return pInstance;
}

CGameObject * CCamera_Debug::Clone_GameObject()
{
	CCamera_Debug* pInstance = new CCamera_Debug(*this);
	if (FAILED(pInstance->Ready_GameObject()))
		Safe_Release(pInstance);
	return pInstance;
}

void CCamera_Debug::Free()
{
	CCamera::Free();
}
