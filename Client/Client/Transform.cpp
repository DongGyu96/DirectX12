#include "stdafx.h"
#include "Transform.h"

CTransform::CTransform(ID3D12Device * pGraphic_Device)
	:CComponent(pGraphic_Device)
{

}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_matWorld(rhs.m_matWorld)
{
}

_vec3 * CTransform::Get_StateInfo(STATE eState)
{
	return (_vec3*)&m_matWorld.m[eState][0];
}

_vec3 CTransform::Get_Scale()
{
	_float			fScaleX = Vector3::Length(*Get_StateInfo(CTransform::STATE_RIGHT));
	_float			fScaleY = Vector3::Length(*Get_StateInfo(CTransform::STATE_UP));
	_float			fScaleZ = Vector3::Length(*Get_StateInfo(CTransform::STATE_LOOK));

	return _vec3(fScaleX, fScaleY, fScaleZ);
}

_matrix CTransform::Get_Matrix_Inverse() const
{
	_matrix mat = m_matWorld;
	mat = Matrix::Inverse(mat);
	return mat;
}

void CTransform::Set_StateInfo(STATE eState, const _vec3 * pInfo)
{
	memcpy(&m_matWorld.m[eState][0], pInfo, sizeof(_vec3));
}

HRESULT CTransform::Ready_Transform()
{
	XMStoreFloat4x4(&m_matWorld, XMMatrixIdentity());
	return S_OK;
}

void CTransform::SetUp_Speed(const _float & fMovePerSec, const _float & fRotationPerSec)
{
	m_fSpeed_Move = fMovePerSec;
	m_fSpeed_Rotation = fRotationPerSec;
}

void CTransform::Go_Straight(const _float & fTimeDelta)
{
	_vec3		vLook, vPosition;
	vLook = *Get_StateInfo(CTransform::STATE_LOOK);
	vPosition = *Get_StateInfo(CTransform::STATE_POSITION);

	vLook = Vector3::Normalize(vLook);
	vLook = Vector3::ScalarProduct(vLook, m_fSpeed_Move*fTimeDelta, false);
	vPosition = Vector3::Add(vPosition, vLook);
	Set_StateInfo(CTransform::STATE_POSITION, &vPosition);
}

void CTransform::BackWard(const _float & fTimeDelta)
{
	_vec3		vLook, vPosition;
	vLook = *Get_StateInfo(CTransform::STATE_LOOK);
	vPosition = *Get_StateInfo(CTransform::STATE_POSITION);

	vLook = Vector3::Normalize(vLook);
	vLook = Vector3::ScalarProduct(vLook, m_fSpeed_Move*-fTimeDelta, false);
	vPosition = Vector3::Add(vPosition, vLook);
	Set_StateInfo(CTransform::STATE_POSITION, &vPosition);
}


void CTransform::Go_Left(const _float & fTimeDelta)
{
	_vec3		vRight, vPosition;

	vRight = *Get_StateInfo(CTransform::STATE_RIGHT);
	vPosition = *Get_StateInfo(CTransform::STATE_POSITION);

	vRight = Vector3::Normalize(vRight);
	vRight = Vector3::ScalarProduct(vRight, m_fSpeed_Move*-fTimeDelta, false);
	vPosition = Vector3::Add(vPosition, vRight);
	Set_StateInfo(CTransform::STATE_POSITION, &vPosition);
}

void CTransform::Go_Right(const _float & fTimeDelta)
{
	_vec3		vRight, vPosition;

	vRight = *Get_StateInfo(CTransform::STATE_RIGHT);
	vPosition = *Get_StateInfo(CTransform::STATE_POSITION);

	vRight = Vector3::Normalize(vRight);
	vRight = Vector3::ScalarProduct(vRight, m_fSpeed_Move*fTimeDelta, false);
	vPosition = Vector3::Add(vPosition, vRight);
	Set_StateInfo(CTransform::STATE_POSITION, &vPosition);
}

void CTransform::SetUp_RotationX(const _float & fRadian)
{
	_vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	_matrix		matRot = Matrix::Identity();
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationX(fRadian)));

	Vector3::ScalarProduct(vRight, Get_Scale().x, false);
	Vector3::ScalarProduct(vUp, Get_Scale().y, false);
	Vector3::ScalarProduct(vLook, Get_Scale().z, false);

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);

	vRight = Vector3::TransformNormal(vRight, mat);
	vUp = Vector3::TransformNormal(vUp, mat);
	vLook = Vector3::TransformNormal(vLook, mat);

	Set_StateInfo(CTransform::STATE_RIGHT, &vRight);
	Set_StateInfo(CTransform::STATE_UP, &vUp);
	Set_StateInfo(CTransform::STATE_LOOK, &vLook);
}

void CTransform::SetUp_RotationY(const _float & fRadian)
{
	_vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	_matrix		matRot = Matrix::Identity();
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(fRadian)));

	Vector3::ScalarProduct(vRight, Get_Scale().x, false);
	Vector3::ScalarProduct(vUp, Get_Scale().y, false);
	Vector3::ScalarProduct(vLook, Get_Scale().z, false);

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);

	vRight = Vector3::TransformNormal(vRight, mat);
	vUp = Vector3::TransformNormal(vUp, mat);
	vLook = Vector3::TransformNormal(vLook, mat);

	Set_StateInfo(CTransform::STATE_RIGHT, &vRight);
	Set_StateInfo(CTransform::STATE_UP, &vUp);
	Set_StateInfo(CTransform::STATE_LOOK, &vLook);
}

void CTransform::SetUp_RotationZ(const _float & fRadian)
{
	_vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	_matrix		matRot = Matrix::Identity();
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(fRadian)));

	Vector3::ScalarProduct(vRight, Get_Scale().x, false);
	Vector3::ScalarProduct(vUp, Get_Scale().y, false);
	Vector3::ScalarProduct(vLook, Get_Scale().z, false);

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);

	vRight = Vector3::TransformNormal(vRight, mat);
	vUp = Vector3::TransformNormal(vUp, mat);
	vLook = Vector3::TransformNormal(vLook, mat);

	Set_StateInfo(CTransform::STATE_RIGHT, &vRight);
	Set_StateInfo(CTransform::STATE_UP, &vUp);
	Set_StateInfo(CTransform::STATE_LOOK, &vLook);
}

void CTransform::Rotation_X(const _float & fTimeDelta)
{
	_vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	_matrix		matRot;
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationX(m_fSpeed_Rotation*fTimeDelta)));

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = Vector3::TransformNormal(vDir[i], mat);


	Set_StateInfo(CTransform::STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(CTransform::STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(CTransform::STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Rotation_Y(const _float & fTimeDelta)
{
	_vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	_matrix		matRot;
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(m_fSpeed_Rotation*-fTimeDelta)));

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = Vector3::TransformNormal(vDir[i], mat);


	Set_StateInfo(CTransform::STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(CTransform::STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(CTransform::STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Rotation_Z(const _float & fTimeDelta)
{
	_vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	_matrix		matRot;
	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(m_fSpeed_Rotation*fTimeDelta)));

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = Vector3::TransformNormal(vDir[i], mat);


	Set_StateInfo(CTransform::STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(CTransform::STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(CTransform::STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Rotation_Axis(const _float & fTimeDelta, const _vec3 * pAxis)
{
	_vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	_matrix			matRot;
	XMVECTOR vAxis = ::XMLoadFloat3(pAxis);

	DirectX::XMStoreFloat4x4(&matRot, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationAxis(vAxis, m_fSpeed_Rotation*fTimeDelta)));

	XMMATRIX mat = ::XMLoadFloat4x4(&matRot);
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = Vector3::TransformNormal(vDir[i], mat);

	Set_StateInfo(CTransform::STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(CTransform::STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(CTransform::STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Scaling(const _float & fX, const _float & fY, const _float & fZ)
{
	_vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
	{
		vDir[i] = *Get_StateInfo(STATE(i));
		Vector3::Normalize(vDir[i]);
	}


	Vector3::ScalarProduct(vDir[STATE_RIGHT], fX, false);
	Vector3::ScalarProduct(vDir[STATE_RIGHT], fY, false);
	Vector3::ScalarProduct(vDir[STATE_RIGHT], fZ, false);


	Set_StateInfo(CTransform::STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(CTransform::STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(CTransform::STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Go_ToTarget(_vec3 * pTargetPos, const _float & fTimeDelta)
{
	_vec3		vLook, vPosition;
	vPosition = *Get_StateInfo(CTransform::STATE_POSITION);

	vLook = Vector3::Subtract(*pTargetPos, vPosition);
	vLook = Vector3::Normalize(vLook);
	vPosition = Vector3::Add(vPosition, vLook);
	vPosition = Vector3::ScalarProduct(vPosition, m_fSpeed_Move*fTimeDelta, false);

	Set_StateInfo(CTransform::STATE_POSITION, &vPosition);
}

CTransform * CTransform::Create(ID3D12Device * pGraphic_Device)
{
	CTransform* pInstance = new CTransform(pGraphic_Device);
	if (FAILED(pInstance->Ready_Transform()))
		Safe_Release(pInstance);
	return pInstance;
}

CComponent * CTransform::Clone_Component()
{
	return new CTransform(*this);
}

void CTransform::Free()
{
	CComponent::Free();
}
