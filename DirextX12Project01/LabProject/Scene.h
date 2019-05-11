#pragma once

#include "GameObject.h"
#include "Player.h"
#include "RailObject.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

	CPlayer						*m_pPlayer = NULL;

	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;

	float setangleY = 0.f;
	float setangleX = 0.f;
	float setangleZ = 0.f;

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void CheckObjectByObjectCollisions();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void BuildRail() {}

};

class CRunAwayScene : public CScene
{
public:
	CRunAwayScene();
	virtual ~CRunAwayScene();

	CTerrainObject				*m_pTerrainObject = NULL;
	vector<RailObject> railObject;
	int buildcount = 0;
	int prevbuildcount = 0;

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void BuildRail(float xangle = 0.0f, float yangle = 0.0f , float zangle = 0.0f);
};
