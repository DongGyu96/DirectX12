#include "stdafx.h"
#include "Scene.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::BuildObjects()
{
}

void CScene::ReleaseObjects()
{
}

void CScene::CheckObjectByObjectCollisions()
{
	
}

void CScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);

	//CheckObjectByObjectCollisions();
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRunAwayScene::CRunAwayScene()
{
}

CRunAwayScene::~CRunAwayScene()
{
}

void CRunAwayScene::BuildObjects()
{
	float fHalfWidth = 250.0f, fHalfHeight = 0.0f, fHalfDepth = 250.0f;
	CTerrainMesh *pTerrainMesh = new CTerrainMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 10);
	pTerrainMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.3f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_pTerrainObject = new CTerrainObject();
	m_pTerrainObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pTerrainObject->SetMesh(pTerrainMesh);
	m_pTerrainObject->SetColor(RGB(0, 0, 0));

	//CTerrainMesh *pTerrainMesh = NULL;

	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	// pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	Rail *rail = new Rail(5.0f, 0.0f, 11.0f, 5);
	// rail->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.5f, 0.5f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_nObjects = 50;
	buildcount = 10;
	prevbuildcount = buildcount - 1;
	m_ppObjects = new CGameObject*[m_nObjects];


	for (int i = 0; i < m_nObjects; ++i)
	{
		m_ppObjects[i] = new RailObject();
		m_ppObjects[i]->SetMesh(rail);
		m_ppObjects[i]->SetColor(RGB(0, 255, 255));
		m_ppObjects[i]->SetMovingSpeed(0.0f);
		m_ppObjects[i]->PassOff();
		if (i < buildcount)
		{
			if (i > 0)
			{
				XMFLOAT3 temp = m_ppObjects[i - 1]->GetEnd();
				m_ppObjects[i]->yangle += m_ppObjects[i - 1]->yangle + 0.0f;
				m_ppObjects[i]->xangle += m_ppObjects[i - 1]->xangle + 0.0f;

				float xradian = Vector3::ToRadian(m_ppObjects[i]->xangle);
				float yradian = Vector3::ToRadian(m_ppObjects[i]->yangle);

				XMFLOAT3 direction = XMFLOAT3(sin(yradian), sin(xradian), cos(yradian));

				temp = Vector3::Add(temp, Vector3::ScalarProduct(direction, 5.f));
				m_ppObjects[i]->SetPosition(temp);

				XMFLOAT3 end = Vector3::Add(temp, Vector3::ScalarProduct(direction, 5.f));
				m_ppObjects[i]->SetEnd(end.x, end.y, end.z);

				XMFLOAT3 start = m_ppObjects[i - 1]->GetEnd();
				m_ppObjects[i]->SetStart(start.x, start.y, start.z);
				m_ppObjects[i]->Rotate(m_ppObjects[i]->xangle, m_ppObjects[i]->yangle, 0.0f);
				m_ppObjects[i]->SetMovingDirection(Vector3::Subtract(m_ppObjects[i]->GetEnd(), m_ppObjects[i]->GetStart(), true));
			}
			else
			{
				m_ppObjects[i]->SetPosition(0.0f, 0.0f, 0.0f);
				m_ppObjects[i]->SetEnd(0.0f, 0.0f, 5.0f);
				m_ppObjects[i]->SetStart(0.0f, 0.0f, -5.0f);
				m_ppObjects[i]->SetMovingDirection(Vector3::Normalize(XMFLOAT3(0.0f, 0.0f, 1.0f)));
			}
		}
		else
		{
			m_ppObjects[i]->SetPosition(0.0f, 0.0f, -50.0f);
			m_ppObjects[i]->PassOn();
		}
	}
}

void CRunAwayScene::ReleaseObjects()
{
	CScene::ReleaseObjects();

	if (m_pTerrainObject) delete m_pTerrainObject;
}

void CRunAwayScene::Animate(float fElapsedTime)
{
	CScene::Animate(fElapsedTime);
	if (Vector3::Distance(m_ppObjects[(m_pPlayer->railcount) % m_nObjects]->GetEnd(), m_pPlayer->GetPosition()) <= 0.4)
	{
		float yangle = m_ppObjects[m_pPlayer->railcount]->yangle;
		float xangle = m_ppObjects[m_pPlayer->railcount]->xangle;

		m_ppObjects[m_pPlayer->railcount]->PassOn();
		m_ppObjects[m_pPlayer->railcount]->SetColor(RGB(0, 0, 0));

		m_pPlayer->railcount++;
		if (m_pPlayer->railcount >= m_nObjects)
			m_pPlayer->railcount = 0;

		if (m_ppObjects[m_pPlayer->railcount]->GetPass())
		{
			setangleX = 0.0f;
			setangleY = 0.0f;
			BuildRail(setangleX, setangleY, 0.0f);
		}

		yangle -= m_ppObjects[m_pPlayer->railcount]->yangle;
		m_pPlayer->yangle += -yangle;

		m_pPlayer->Rotate(0.f, -yangle, 0.f);

		m_pPlayer->SetPosition(m_ppObjects[m_pPlayer->railcount]->GetStart());

	}

	CScene::CheckObjectByObjectCollisions();
}

void CRunAwayScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	m_pTerrainObject->Render(hDCFrameBuffer, pCamera);

	CScene::Render(hDCFrameBuffer, pCamera);
}

void CRunAwayScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			setangleY = 22.5f;
			BuildRail(setangleX, setangleY, 0.0f);
			setangleY = 0.f;
			break;
		case VK_LEFT:
			setangleY = -22.5f;
			BuildRail(setangleX, setangleY, 0.0f);
			setangleY = 0.f;
			break;
		case VK_UP:
			setangleY = 0.f;
			setangleX = 22.5f;
			BuildRail(setangleX, setangleY, 0.0f);
			setangleX = 0.f;
			break;
		case VK_DOWN:
			setangleY = 0.f;
			setangleX = -22.5f;
			BuildRail(setangleX, setangleY, 0.0f);
			setangleX = 0.f;
			break;
		case VK_SPACE:
			BuildRail(setangleX, setangleY, 0.0f);
			break;
		case NUM_ONE:
			if (setangleX < 0.0f)
				setangleX = 0.0f;

			if (setangleX + 5.f < 45.f) {
				setangleX += 5.f;
				cout << "X : " << setangleX << "\t Y : " << setangleY << endl;
			}
			break;
		case NUM_TWO:
			if (setangleX > 0.0f)
				setangleX = 0.0f;

			if (setangleX - 5.f > -45.f) {
				setangleX -= 5.f;
				cout << "X : " << setangleX << "\t Y : " << setangleY << endl;
			}
			break;
		case NUM_THREE:
			if (setangleY < 0.0f)
				setangleY = 0.0f;

			if (setangleY + 5.f < 65.f) {
				setangleY += 5.f;
				cout << "X : " << setangleX << "\t Y : " << setangleY << endl;
			}
			break;
		case NUM_FOUR:
			if (setangleY > 0.0f)
				setangleY = 0.0f;

			if (setangleY - 5.f > -65.f) {
				setangleY -= 5.f;
				cout << "X : " << setangleX << "\t Y : " << setangleY << endl;
			}
			break;
		case NUM_ZERO:
			setangleX = 0.f;
			setangleY = 0.f;
			cout << "X : " << setangleX << "\t Y : " << setangleY << endl;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CRunAwayScene::BuildRail(float xangle, float yangle, float zangle)
{
	if (m_ppObjects[buildcount]->GetPass())
	{
		m_ppObjects[buildcount]->SetMatrix();
		m_ppObjects[buildcount]->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
		//m_ppObjects[m_pPlayer->railcount];
		XMFLOAT3 temp = m_ppObjects[prevbuildcount]->GetEnd();
		//m_ppObjects[buildcount]->SetMatrix(m_ppObjects[buildcount]->GetMatrix());

		m_ppObjects[buildcount]->yangle = m_ppObjects[prevbuildcount]->yangle + yangle;
		m_ppObjects[buildcount]->xangle = m_ppObjects[prevbuildcount]->xangle + xangle;

		float xradian = Vector3::ToRadian(m_ppObjects[buildcount]->xangle);
		float yradian = Vector3::ToRadian(m_ppObjects[buildcount]->yangle);
		float zradian = Vector3::ToRadian(zangle);

		//XMFLOAT3 direction = XMFLOAT3(sin(yradian), sin(xradian), cos(yradian));

		XMFLOAT4X4 tempMatrix;

		tempMatrix = Matrix4x4::RotationYawPitchRoll(-m_ppObjects[buildcount]->xangle, m_ppObjects[buildcount]->yangle, zangle);

		XMFLOAT3 direction = Vector3::Normalize(Vector3::TransformNormal(XMFLOAT3(0.0f, 0.0f, 1.0f), tempMatrix));

		m_ppObjects[buildcount]->Rotate(-m_ppObjects[buildcount]->xangle, m_ppObjects[buildcount]->yangle, 0.0f);


		temp = Vector3::Add(temp, Vector3::ScalarProduct(direction, 5.f));
		m_ppObjects[buildcount]->SetPosition(temp);

		XMFLOAT3 end = Vector3::Add(temp, Vector3::ScalarProduct(direction, 5.f));
		m_ppObjects[buildcount]->SetEnd(end.x, end.y, end.z);

		XMFLOAT3 start = m_ppObjects[prevbuildcount]->GetEnd();
		m_ppObjects[buildcount]->SetStart(start.x, start.y, start.z);
		m_ppObjects[buildcount]->SetMovingDirection(Vector3::Subtract(m_ppObjects[buildcount]->GetEnd(), m_ppObjects[buildcount]->GetStart(), true));

		m_ppObjects[buildcount]->PassOff();
		m_ppObjects[buildcount]->SetColor(RGB(0, 255, 255));
		buildcount++;
		if (buildcount >= m_nObjects)
			buildcount = 0;
		prevbuildcount++;
		if (prevbuildcount >= m_nObjects)
			prevbuildcount = 0;
	}
}