#pragma once
#include "Component.h"
class CTransform :public CComponent
{
public:
	enum STATE {STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END};
private:
	CTransform(ID3D12Device* pGraphic_Device);
	CTransform(const CTransform& rhs);
	~CTransform()=default;
public:
	_vec3*					Get_StateInfo(STATE eState);
	_vec3					Get_Scale();
	_matrix					Get_Matrix() { return m_matWorld; }
	const _matrix*			Get_Matrix_Pointer()const { return &m_matWorld; }
	_matrix					Get_Matrix_Inverse()const;
public:
	void					Set_StateInfo(STATE eState, const _vec3* pInfo);
	void					Set_PositionY(const _float& Y) { m_matWorld.m[3][1] = Y; }
public:
	HRESULT					Ready_Transform();
public:
	void					SetUp_Speed(const _float& fMovePerSec, const _float& fRotationPerSec);
	void					Go_Straight(const _float& fTimeDelta);
	void					BackWard(const _float& fTimeDelta);
	void					Go_Left(const _float& fTimeDelta);
	void					Go_Right(const _float& fTimeDelta);
	void					SetUp_RotationX(const _float& fRadian);
	void					SetUp_RotationY(const _float& fRadian);
	void					SetUp_RotationZ(const _float& fRadian);
	void					Rotation_X(const _float& fTimeDelta);
	void					Rotation_Y(const _float& fTimeDelta);
	void					Rotation_Z(const _float& fTimeDelta);
	void					Rotation_Axis(const _float& fTimeDelta, const _vec3* pAxis);
	void					Scaling(const _float& fX, const _float& fY, const _float& fZ);
	void					Go_ToTarget(_vec3* pTargetPos, const _float& fTimeDelta);
private:
	_matrix					m_matWorld;
	_float					m_fSpeed_Move = 0.f;
	_float					m_fSpeed_Rotation = 0.f;
public:
	static	CTransform*		Create(ID3D12Device* pGraphic_Device);
	virtual CComponent*		Clone_Component();
	virtual void			Free();
};

