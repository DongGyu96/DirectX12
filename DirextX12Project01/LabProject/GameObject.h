#pragma once

#include "Mesh.h"
#include "Camera.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CGameObject
{
public:
	CGameObject(CMesh *pMesh);
	CGameObject();
	virtual ~CGameObject();

public:
	bool						m_bActive = true;
	
	CMesh						*m_pMesh = NULL;
    XMFLOAT4X4					m_xmf4x4World;    

	BoundingOrientedBox			m_xmOOBB;

	CGameObject					*m_pObjectCollided = NULL;

	DWORD						m_dwColor;

	XMFLOAT3					m_xmf3MovingDirection;
	float						m_fMovingSpeed = 0.0f;
	float						m_fMovingRange = 0.0f;

	XMFLOAT3 start;
	XMFLOAT3 end;
	float yangle = 0.f;
	float xangle = 0.f;

	XMFLOAT3					m_xmf3RotationAxis;
	float						m_fRotationSpeed = 0.0f;

public:
	void SetMatrix();
	void SetMatrix(XMFLOAT4X4 matrix) { m_xmf4x4World = matrix; }
	XMFLOAT4X4 GetMatrix() { return m_xmf4x4World; }
	void SetMesh(CMesh *pMesh) { m_pMesh = pMesh; if (pMesh) pMesh->AddRef(); }
	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3& xmf3Position);

	void SetStart(float x, float y, float z) { start = XMFLOAT3(x, y, z); }
	void SetEnd(float x, float y, float z) { end = XMFLOAT3(x, y, z); }
	XMFLOAT3 GetStart() { return start; }
	XMFLOAT3 GetEnd() { return end; }


	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingRange(float fRange) { m_fMovingRange = fRange; }

	void SetRotationAxis(XMFLOAT3& xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }
	void SetRotationSpeed(float fSpeed) { m_fRotationSpeed = fSpeed; }

	void MoveStrafe(float fDistance=1.0f);
	void MoveUp(float fDistance=1.0f);
	void MoveForward(float fDistance=1.0f);
	void Move(XMFLOAT3& vDirection, float fDistance);

	void Rotate(float fPitch=10.0f, float fYaw=10.0f, float fRoll=10.0f);
	void Rotate(XMFLOAT3& xmf3Axis, float fAngle);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	XMFLOAT3 GetMovingDirection() { return m_xmf3MovingDirection; }

	virtual void Animate(float fElapsedTime);
	virtual void OnPreRender() { }
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
	virtual void PassOn() {}
	virtual void PassOff() {}
	virtual bool GetPass() { return false; }
};

class CTerrainObject : public CGameObject
{
public:
	CTerrainObject();
	virtual ~CTerrainObject();
};

class CFollowerObject : public CGameObject
{
public:
	CFollowerObject(CGameObject *pTarget);
	virtual ~CFollowerObject();

	CGameObject					*m_pTarget = NULL;
	XMFLOAT3					m_xmf3InitialPosition;

	virtual void Animate(float fElapsedTime);
};


