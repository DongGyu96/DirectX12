#pragma once
#include "Base.h"
#include "Renderer.h"
#include "Combine.h"
class CManagement;
class CMainApp:public CBase
{
public:
	CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT Ready_MainApp();
	_int	Update_MainApp(const _float& fTimeDelta);
	void	Render_MainApp();
public:
	HRESULT	Ready_Start_Scene(SCENEID eSceneID);
public:
	HRESULT Ready_Prototype_Component();

private:
	_tchar	m_szFPS[MAX_PATH] = L"";
	_ulong	m_dwRenderCnt = 0;
	_float	m_fTimeAcc = 0.f;
private:
	CRenderer*		m_pRenderer = nullptr;
	CCombine*		m_pCombine = nullptr;
private:
	ID3D12Device*		m_pGraphic_Device = nullptr;
	CManagement* m_pManagement = nullptr;
public:
	static CMainApp*		Create();
	virtual void Free();

};

